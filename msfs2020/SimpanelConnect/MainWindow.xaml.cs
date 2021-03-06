﻿using System;
using System.Collections.Generic;
using System.Collections.Concurrent;
using System.Windows;
using System.Windows.Forms;
using System.Windows.Media;
using System.IO.Ports;
using System.Threading;
using Microsoft.FlightSimulator.SimConnect;
using System.Runtime.InteropServices;
using System.Windows.Interop;
using System.Xml;

namespace SimpanelConnect
{
    public partial class MainWindow : Window
    {
        static BlockingCollection<String> spout;
        static Thread usbthread;
        static Thread simthread;
        static EventWaitHandle sim_message;
        private const uint WIN32_SIMCONNECT_EVENT = 0x0402;
        private volatile IntPtr hWnd;
        private System.Windows.Forms.NotifyIcon systray;
        static bool quitting;
        public MainWindow()
        {
            InitializeComponent();

            // Assembly me = typeof(MainWindow).Assembly;

            systray = new System.Windows.Forms.NotifyIcon();
            systray.BalloonTipTitle = "Simpanel Connect";
            systray.Text = "Simpanel";
            systray.Click += new EventHandler(systray_click);
            //Uri iconUri = new Uri("pack://application:,,,/simpanel_eWa_icon.ico", UriKind.Absolute);
            systray.Icon = new System.Drawing.Icon(typeof(MainWindow), "simpanel_eWa_icon.ico");

            quitting = false;

            usbthread = new Thread(USB_Handler);
            usbthread.Start();

            hWnd = new WindowInteropHelper(this).EnsureHandle();
            HwndSource router = HwndSource.FromHwnd(hWnd);
            router.AddHook(this.onWindowProc);

            sim_message = new EventWaitHandle(false, EventResetMode.AutoReset);
            simthread = new Thread(SIM_Handler);
            simthread.Start();
        }

        struct ControlsState
        {
            Int16 hgd_dial;
            Int16 spd_dial;
            Int16 vs_dial;
            Int16 alt_dial;
            bool alt_but;
            bool spd_mach;
            bool hgd_led, at_led, flc_led, vnav_led, lnav_led, vs_led, alt_led, f4_led, f3_led, f2_led, f1_led;
        }

        struct InputState
        {
            internal int dial_hdg;
            internal int dial_spd;
            internal int dial_vs;
            internal int dial_alt;
            internal Byte sw_ap1;
            internal Byte sw_ap2;
            internal Byte sw_onoff;
            internal Byte sw_moment;
            internal Byte sw_others;
            internal Byte sw_dial;
        }

        enum SC_CLIENTDATA
        {
            SPDisplayCD, SPInputCD,
        }
        enum SC_REQUEST
        {
            SPDisplayReq, SPInputReq,
        };

        enum SC_DATA
        {
            SPDisplayData, SPInputData,
        };

        enum SC_EVENT
        {
            SPDisplayEvent, SPInputEvent,
        };

        enum SC_GROUP
        {
            SPGroup,
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
        struct SPDisplayStruct
        {
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
            public string data;
        };

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
        struct SPInputStruct
        {
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
            public string data;
        };

        static private SPDisplayStruct sp_display;
        static private SPInputStruct sp_input;
   
        private IntPtr onWindowProc(IntPtr hwnd, int msg, IntPtr wParam, IntPtr lParam, ref bool handled)
        {
            if (msg == WIN32_SIMCONNECT_EVENT)
            {
                sim_message.Set();
                handled = true;
            }
            else
            {
                handled = false;
            }
            return IntPtr.Zero;
        }

        void _sim_open(SimConnect sim, SIMCONNECT_RECV data)
        {
            this.Dispatcher.Invoke(new Action(() => sim_connected()));

            sim.MapClientDataNameToID("simpanel.display", SC_CLIENTDATA.SPDisplayCD);
            sim.CreateClientData(SC_CLIENTDATA.SPDisplayCD, 32, SIMCONNECT_CREATE_CLIENT_DATA_FLAG.READ_ONLY);
            sim.AddToClientDataDefinition(SC_DATA.SPDisplayData, 0, 32, 0, 0);
            sim.RegisterStruct<SIMCONNECT_RECV_CLIENT_DATA, SPDisplayStruct>(SC_DATA.SPDisplayData);

            sim.MapClientDataNameToID("simpanel.input", SC_CLIENTDATA.SPInputCD);
            sim.CreateClientData(SC_CLIENTDATA.SPInputCD, 32, 0);
            sim.AddToClientDataDefinition(SC_DATA.SPInputData, 0, 32, 0, 0);
            sim.RegisterStruct<SIMCONNECT_RECV_CLIENT_DATA, SPInputStruct>(SC_DATA.SPInputData);

            sim.MapClientEventToSimEvent(SC_EVENT.SPDisplayEvent, "simpanel.display");
            sim.MapClientEventToSimEvent(SC_EVENT.SPInputEvent, "simpanel.input");

            sim.AddClientEventToNotificationGroup(SC_GROUP.SPGroup, SC_EVENT.SPDisplayEvent, false);
            sim.SetNotificationGroupPriority(SC_GROUP.SPGroup, SimConnect.SIMCONNECT_GROUP_PRIORITY_HIGHEST);

            sim.RequestClientData(SC_CLIENTDATA.SPDisplayCD, SC_REQUEST.SPDisplayReq, SC_DATA.SPDisplayData, SIMCONNECT_CLIENT_DATA_PERIOD.ON_SET, SIMCONNECT_CLIENT_DATA_REQUEST_FLAG.CHANGED, 0, 0, 0);
            sim.TransmitClientEvent(SimConnect.SIMCONNECT_OBJECT_ID_USER, SC_EVENT.SPInputEvent, 0, SC_GROUP.SPGroup, SIMCONNECT_EVENT_FLAG.DEFAULT);
        }

        void _sim_quit(SimConnect sim, SIMCONNECT_RECV data)
        {
            this.Dispatcher.Invoke(new Action(() => sim_disconnected()));
        }

        void _sim_frame(SimConnect sim, SIMCONNECT_RECV_EVENT data)
        {
            this.Dispatcher.Invoke(new Action(() => sim_frame(sim)));
        }

        void _sim_data(SimConnect sim, SIMCONNECT_RECV_CLIENT_DATA data)
        {
            switch((SC_REQUEST)data.dwRequestID)
            {
                case SC_REQUEST.SPDisplayReq:
                    sp_display = (SPDisplayStruct)data.dwData[0];
                    this.Dispatcher.Invoke(new Action(() => sim_fsdata()));
                    break;
            }
        }

        private static SimConnect sim = null;

        private void SIM_Handler()
        {
            while (!quitting)
            {
                if (sim == null)
                {
                    this.Dispatcher.Invoke(new Action(() => sim_connecting()));

                    try
                    {
                        sim = new SimConnect("SIMPANEL", hWnd, WIN32_SIMCONNECT_EVENT, null, 0);
                        sim.OnRecvOpen += _sim_open;
                        sim.OnRecvQuit += _sim_quit;
                        sim.OnRecvClientData += _sim_data;
                    }
                    catch
                    {
                        sim = null;
                        this.Dispatcher.Invoke(new Action(() => sim_disconnected()));
                        Thread.Sleep(5000);
                        continue;
                    }
                }

                try
                {
                    while (!quitting)
                    {
                        sim_message.WaitOne();
                        if(!quitting)
                            sim.ReceiveMessage();
                    }
                }
                catch
                {
                }

                if (!quitting)
                {
                    this.Dispatcher.Invoke(new Action(() => sim_disconnected()));
                    sim.Dispose();
                    sim = null;
                    Thread.Sleep(5000);
                }
            }

            if (sim != null)
                sim.Dispose();
        }

        public void USB_Writer(Object com)
        {
            while (!quitting)
            {
                string s = spout.Take();
                ((SerialPort)com).WriteLine(s);
            }
        }

        public void USB_Handler()
        {
            SerialPort com = new SerialPort();
            List<string> ports = new List<string>(SerialPort.GetPortNames());
            ports.Sort();
            ports.Reverse();

            while (!quitting)
            {

                string r = null;
                foreach (string port in ports)
                {
                    com.PortName = port;
                    com.BaudRate = 57600;
                    com.ReadTimeout = 200;
                    com.WriteTimeout = 200;
                    try
                    {
                        com.Open();
                    }
                    catch
                    {
                        r = null;
                        continue;
                    }

                    try
                    {
                        com.WriteLine("\nxs");
                        while(!quitting)
                        {
                            r = com.ReadLine();
                            if (r.StartsWith("XS"))
                                break;
                        }
                    }
                    catch(Exception e)
                    {
                        com.Close();
                        r = null;
                    }

                    if (r != null && r.StartsWith("XS"))
                        break;
                }

                if (!quitting && r != null && r.StartsWith("XS"))
                {
                    com.ReadTimeout = 500;
                    com.WriteTimeout = SerialPort.InfiniteTimeout;
                    Thread writer = new Thread(USB_Writer);
                    spout = new BlockingCollection<string>();
                    writer.Start(com);

                    try
                    {
                        spout.Add("v");
                        this.Dispatcher.Invoke(new Action(() => usb_connected(com.PortName)));

                        while (!quitting)
                        {
                            try
                            {
                                string line = com.ReadLine().TrimEnd('\r', '\n');

                                this.Dispatcher.BeginInvoke(new Action(() => recv_usb(line)));
                            }
                            catch (TimeoutException)
                            {
                            }
                        }
                    }
                    catch
                    {
                    }
                    finally
                    {
                        com.Close();
                        writer.Abort();
                        writer.Join();
                        spout.Dispose();
                        spout = null;
                    }
                }
                else
                    r = "No SIMPANEL found";

                if (!quitting)
                {
                    this.Dispatcher.Invoke(new Action(() => usb_disconnected(r)));
                    Thread.Sleep(1000);
                }
            }
        }

        private static Brush active_green = (SolidColorBrush)new BrushConverter().ConvertFromString("#FF8FFF8F");
        private static Brush inactive_red = (SolidColorBrush)new BrushConverter().ConvertFromString("#FFFF8F8F");

        private void recv_usb(String usb)
        {
            switch (usb[0])
            {
                case 'M':
                    panelInterface.Text = usb.Substring(1);
                    break;
                case 'V':
                    panelProtocol.Text = usb.Substring(1);
                    break;
                case 'I':
                    panelBoard.Text = usb.Substring(2);
                    break;
                case 'S':
                    this.Dispatcher.Invoke(new Action(() => panel_input(usb.Substring(1))));
                    break;
                default:
                    break;
            }
        }

        private bool usb_is_connected = false;
        private bool sim_is_connected = false;

        private void balloon()
        {
            string msg = usb_is_connected ? "Simpanel connected" : "No Simpanel found";
            msg += "\n";
            msg += sim_is_connected ? "Simulator connected" : "No simulator";
            systray.BalloonTipText = msg;
            systray.ShowBalloonTip(20000, "Simpanel Connect", msg, (sim_is_connected && usb_is_connected) ? ToolTipIcon.Info : ToolTipIcon.Warning);
        }
        private void sim_status()
        {
            if (spout != null)
                spout.Add(sim_is_connected ? "mwqqq5IMIDLEqqqqqq" : "mwqN05IMqqqqqqqqqq");
        }
        private void usb_connected(String port)
        {
            panelStatusBG.Background = active_green;
            panelStatusText.Text = port;
            usb_is_connected = true;
            sim_status();
            balloon();
            if(sim_is_connected)
                sim.TransmitClientEvent(SimConnect.SIMCONNECT_OBJECT_ID_USER, SC_EVENT.SPInputEvent, 0, SC_GROUP.SPGroup, SIMCONNECT_EVENT_FLAG.DEFAULT);
        }

        private void usb_disconnected(String reason)
        {
            panelStatusBG.Background = inactive_red;
            panelStatusText.Text = "Disconnected";
            usb_is_connected = false;
            balloon();
        }

        private void sim_connecting()
        {
            simStatusBG.Background = inactive_red;
            simStatusText.Text = "Connecting";
        }

        private void sim_connected()
        {
            simStatusBG.Background = active_green;
            simStatusText.Text = "Connected";
            sim_is_connected = true;
            sim_status();
            balloon();
        }

        private void sim_disconnected()
        {
            simStatusBG.Background = inactive_red;
            simStatusText.Text = "Disconnected";
            if (sim_is_connected)
            {
                sim_is_connected = false;
                sim_status();
                balloon();
            }

        }

        private void sim_fsdata()
        {
            simType.Text = sp_display.data.Substring(0,4);
            string os = "";
            for (int i = 0; i < 16; i++)
            {
                char c = sp_display.data[4 + i];

                switch (c)
                    {
                        case '+':
                            os += 'v';
                            break;
                        case '-':
                            os += 'j';
                            break;
                        case ' ':
                        default:
                            if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 's') || (c >= 'A' && c <= 'S'))
                                os += c;
                            else
                            os += 'q';
                            break;
                    }
            }
            if (spout != null)
            {
                spout.Add("mw" + os);
                spout.Add("ma" + sp_display.data.Substring(20, 3));
            }
        }

        private static InputState cur_is;
        private void panel_input(string s)
        {
            sp_input.data = s;
            sim.SetClientData(SC_CLIENTDATA.SPInputCD, SC_DATA.SPInputData, SIMCONNECT_CLIENT_DATA_SET_FLAG.DEFAULT, 0, sp_input);
        }


        private void sim_frame(SimConnect sim)
        {
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            systray.Dispose();
            systray = null;
            quitting = true;
            sim_message.Set();
            usbthread.Join();
            simthread.Join();
            //try { usbthread.Abort(); } catch(System.ObjectDisposedException ex) { }
            //try { simthread.Abort(); } catch(System.ObjectDisposedException ex) { }
        }

        private void Window_StateChanged(object sender, EventArgs e)
        {
            if(WindowState == WindowState.Minimized)
                Hide();
            balloon();
        }

        private void Window_IsVisibleChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            if(systray != null)
                systray.Visible = !IsVisible;
        }
        private void systray_click(object sender, EventArgs e)
        {
            Show();
            WindowState = WindowState.Normal;
        }

    }
}

     
