#include "helper.h"

#if defined( _DEBUG )
bool __IsError( const int error, const char* file, const int line, const char* func, const char* command )
{
    if ( error == CG_OK ) { return false; }

    // Output message tag.
    std::string message_tag( "CGNS ERROR" );
    std::cerr << KVS_MESSAGE_SET_COLOR( KVS_MESSAGE_RED );
    std::cerr << message_tag;
    std::cerr << KVS_MESSAGE_RESET_COLOR;

    // Output message with an error string.
    std::string error_string;
    const char* c = cg_get_error();
    while ( *c ) error_string += *c++;
    std::cerr << ": " << error_string << std::endl;
    std::cerr << "\t" << "FILE: " << file << " (" << line << ")" << std::endl;
    std::cerr << "\t" << "FUNC: " << func << std::endl;
    std::cerr << "\t" << "CGNS COMMAND: " << command << std::endl;

    return true;
}
#endif // defined(_DEBUG)

const std::string indents(const int i) {
    return std::string(i * 2, ' ');
}
