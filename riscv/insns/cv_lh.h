require_extension(EXT_XCOREV);
WRITE_RD(zext32(MMU.load<int16_t>(RS1)));
