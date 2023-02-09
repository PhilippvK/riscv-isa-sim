require_extension(EXT_XCOREV);
// MMU.store<uint16_t>(RS1, RS2);
WRITE_RD(sext_xlen(RS1 + RS2));
