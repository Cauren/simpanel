#! /usr/bin/perl

my @data;
my $palette = '';
my @palette;
my $w;
my $h;
my $nc;
my $ch;
my $name = shift;

while(<>) {
    chomp;
    next if m|^/\*|;
    next if m/^\s*static\s+char\s*\*\s*(\S+)\s*\[\s*\]/;
    if(m/^"([0-9]+)\s+([0-9]+)\s+([0-9]+)\s+([0-9]+)\s*",$/) {
	($w, $h, $nc, $ch) = ($1, $2, $3, $4);
	next;
    }
    if(m/^"(.)\s+c (\S+)",$/) {
	next if $2 eq 'None';
	$palette[length $palette] = $2;
	$palette .= $1;
	next;
    }
    next unless m/^"(.*)"(:?,|};|)$/;
    s//\1/;
    push @data, map { index $palette, $_ } split(//);
}

my @col = 0 x $w;
my $skip = 0;
my $repeat = 0;
my $x = 0;
my @out;

while($#data >= 0) {
    if($col[$x] eq $data[0]) {
	my $skip = 0;
	$skip++  while $skip<130 and $skip<=$#data and $col[($x+$skip) % $w] eq $data[$skip];
	if($skip>2) {
	    push @out, $skip-3;
	    $x = ($x + $skip) % $w;
	    splice @data, 0, $skip;
	    next;
	}
    }
    my $prev = $col[($x+$w-1) % $w];
    if($prev eq $data[0]) {
	my $repeat = 0;
	$repeat++  while $repeat<66 and $repeat<=$#data and $data[$repeat] eq $prev;
	if($repeat>2) {
	    push @out, 0x80 | ($repeat-3);
	    my $fill = $repeat<$w? $repeat: $w;
	    for(my $i=0; $i<$fill; $i++) {
		$col[($x + $i) % $w] = $prev;
	    }
	    # $col[($x + $fill) % $w] = $prev  while --$fill;
	    $x = ($x + $repeat) % $w;
	    splice @data, 0, $repeat;
	    next;
	}
    }
    if($#data > 0) {
	push @out, 0xC0 | ($data[0]<<3) | $data[1];
	$col[$x++] = shift @data;
	$x %= $w;
    } else {
	push @out, 0xC0 | ($data[0]<<3);
    }
    $col[$x++] = shift @data;
    $x %= $w;
}

print "static const unsigned char img_${name}[] PROGMEM = { $w, $h,\n\t";
$x = -1;
foreach my $o (@out) {
    if($x++ > 15) {
	$x = 0;
	print "\n\t";
    }
    if(($o&0xC0)==0xC0) {
	printf "0%03o, ", $o;
    } else {
	printf "0x%02X, ", $o;
    }
}
print "\n};\n";

