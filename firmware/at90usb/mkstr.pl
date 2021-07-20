#! /usr/bin/perl

my %str;
my @order;
while(<>) {
    next unless m/^(\S+)\s+(.*)$/;
    $str{$1} = $2;
    push @order, $1;
}
my $num = 2;
print "enum StringIndex_t { SI_language=0, SI_serial=1,\n";
foreach my $s (@order) {
    print "SI_$s = ", $num++, ",\n";
}
print "};\n";
foreach my $s (@order) {
    print "const USB_Descriptor_String_t PROGMEM STR_$s = USB_STRING_DESCRIPTOR(L\"$str{$s}\");\n";
}
print "const USB_Descriptor_String_t PROGMEM STR_languagestring = USB_STRING_DESCRIPTOR_ARRAY(LANGUAGE_ID_ENG);\n";
print "const PGM_VOID_P const PROGMEM Strings[] = {\n&STR_languagestring, 0,\n";
foreach my $s (@order) {
    print "&STR_$s,\n";
}
print "};\n";
