#ifndef WEIGHT_ENGINE__UTILS__LOG_H
#define WEIGHT_ENGINE__UTILS__LOG_H
#include <memory>
#include <string>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Weight{
  class WEIGHT_API Log{
  private:
    static std::shared_ptr<spdlog::logger> engine_logger;
    static std::shared_ptr<spdlog::logger> app_logger;
  public:
    static void init(std::string name);

    inline static std::shared_ptr<spdlog::logger>& get_engine_logger(){return engine_logger;}
    inline static std::shared_ptr<spdlog::logger>& get_app_logger(){return app_logger;}

    inline static std::string decode_freetype_error(int error){
      switch(error){
        case 0x00:
            return "no error";
        case 0x01:
            return "cannot open resource";
        case 0x02:
            return "unknown file format";
        case 0x03:
            return "broken file";
        case 0x04:
            return "invalid FreeType version";
        case 0x05:
            return "module version is too low";
        case 0x06:
            return "invalid argument";
        case 0x07:
            return "unimplemented feature";
        case 0x08:
            return "broken table";
        case 0x09:
            return "broken offset within table";
        case 0x0A:
            return "array allocation size too large";
        case 0x0B:
            return "missing module";
        case 0x0C:
            return "missing property";
        case 0x10:
            return "invalid glyph index";
        case 0x11:
            return "invalid character code";
        case 0x12:
            return "unsupported glyph image format";
        case 0x13:
            return "cannot render this glyph format";
        case 0x14:
            return "invalid outline";
        case 0x15:
            return "invalid composite glyph";
        case 0x16:
            return "too many hints";
        case 0x17:
            return "invalid pixel size";
        case 0x20:
            return "invalid object handle";
        case 0x21:
            return "invalid library handle";
        case 0x22:
            return "invalid module handle";
        case 0x23:
            return "invalid face handle";
        case 0x24:
            return "invalid size handle";
        case 0x25:
            return "invalid glyph slot handle";
        case 0x26:
            return "invalid charmap handle";
        case 0x27:
            return "invalid cache manager handle";
        case 0x28:
            return "invalid stream handle";
        case 0x30:
            return "too many modules";
        case 0x31:
            return "too many extensions";
        case 0x40:
            return "out of memory";
        case 0x41:
            return "unlisted object";
        case 0x51:
            return "cannot open stream";
        case 0x52:
            return "invalid stream seek";
        case 0x53:
            return "invalid stream skip";
        case 0x54:
            return "invalid stream read";
        case 0x55:
            return "invalid stream operation";
        case 0x56:
            return "invalid frame operation";
        case 0x57:
            return "nested frame access";
        case 0x58:
            return "invalid frame read";
        case 0x60:
            return "raster uninitialized";
        case 0x61:
            return "raster corrupted";
        case 0x62:
            return "raster overflow";
        case 0x63:
            return "negative height while rastering";
        case 0x70:
            return "too many registered caches";
        case 0x80:
            return "invalid opcode";
        case 0x81:
            return "too few arguments";
        case 0x82:
            return "stack overflow";
        case 0x83:
            return "code overflow";
        case 0x84:
            return "bad argument";
        case 0x85:
            return "division by zero";
        case 0x86:
            return "invalid reference";
        case 0x87:
            return "found debug opcode";
        case 0x88:
            return "found ENDF opcode in execution stream";
        case 0x89:
            return "nested DEFS";
        case 0x8A:
            return "invalid code range";
        case 0x8B:
            return "execution context too long";
        case 0x8C:
            return "too many function definitions";
        case 0x8D:
            return "too many instruction definitions";
        case 0x8E:
            return "SFNT font table missing";
        case 0x8F:
            return "horizontal header (hhea) table missing";
        case 0x90:
            return "locations (loca) table missing";
        case 0x91:
            return "name table missing";
        case 0x92:
            return "character map (cmap) table missing";
        case 0x93:
            return "horizontal metrics (hmtx) table missing";
        case 0x94:
            return "PostScript (post) table missing";
        case 0x95:
            return "invalid horizontal metrics";
        case 0x96:
            return "invalid character map (cmap) format";
        case 0x97:
            return "invalid ppem value";
        case 0x98:
            return "invalid vertical metrics";
        case 0x99:
            return "could not find context";
        case 0x9A:
            return "invalid PostScript (post) table format";
        case 0x9B:
            return "invalid PostScript (post) table";
        case 0x9C:
            return "found FDEF or IDEF opcode in glyf bytecode";
        case 0x9D:
            return "missing bitmap in strike";
        case 0xA0:
            return "opcode syntax error";
        case 0xA1:
            return "argument stack underflow";
        case 0xA2:
            return "ignore";
        case 0xA3:
            return "no Unicode glyph name found";
        case 0xA4:
            return "glyph too big for hinting";
        case 0xB0:
            return "`STARTFONT' field missing";
        case 0xB1:
            return "`FONT' field missing";
        case 0xB2:
            return "`SIZE' field missing";
        case 0xB3:
            return "`FONTBOUNDINGBOX' field missing";
        case 0xB4:
            return "`CHARS' field missing";
        case 0xB5:
            return "`STARTCHAR' field missing";
        case 0xB6:
            return "`ENCODING' field missing";
        case 0xB7:
            return "`BBX' field missing";
        case 0xB8:
            return "`BBX' too big";
        case 0xB9:
            return "Font header corrupted or missing fields";
        case 0xBA:
            return "Font glyphs corrupted or missing fields";
        default:
            return "Unknown FreeType error code";
      }
    }
  };

}

#ifdef WEIGHT_DEBUG
#define WEIGHT_LOG(...) Weight::Log::get_engine_logger()->trace(__VA_ARGS__)
#define WEIGHT_SUCCESS(...) Weight::Log::get_engine_logger()->info(__VA_ARGS__)
#define WEIGHT_WARNING(...) Weight::Log::get_engine_logger()->warn(__VA_ARGS__)
#define WEIGHT_ERROR(...) Weight::Log::get_engine_logger()->error(__VA_ARGS__)

#define LOG(...) Weight::Log::get_app_logger()->trace(__VA_ARGS__)
#define SUCCESS(...) Weight::Log::get_app_logger()->info(__VA_ARGS__)
#define WARNING(...) Weight::Log::get_app_logger()->warn(__VA_ARGS__)
#define ERROR(...) Weight::Log::get_app_logger()->error(__VA_ARGS__)

#define DECODE_FREETYPE_ERROR(...) Weight::Log::decode_freetype_error(__VA_ARGS__)

#else

#define WEIGHT_LOG(...) //
#define WEIGHT_SUCCESS(...) //
#define WEIGHT_WARNING(...) //
#define WEIGHT_ERROR(...) //

#define LOG(...) //
#define SUCCESS(...) //
#define WARNING(...) //
#define ERROR(...) //

#define DECODE_FREETYPE_ERROR(...) //

#endif
#endif
