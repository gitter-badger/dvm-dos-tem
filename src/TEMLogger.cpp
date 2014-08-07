#include <boost/log/expressions/formatters/named_scope.hpp>

#include "TEMLogger.h"

// Create the global logger object
src::severity_logger< severity_level > glg;


// Add a bunch of attributes to it
BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", severity_level)
BOOST_LOG_ATTRIBUTE_KEYWORD(pid, "ProcessID", attrs::current_process_id::value_type)
BOOST_LOG_ATTRIBUTE_KEYWORD(named_scope, "Scope", attrs::named_scope::value_type)


/** Initialize the enum parser map from strings to the enum levels.*/
template<>
EnumParser< severity_level >::EnumParser() {
    enumMap["debug"] = debug;
    enumMap["info"] = info;
    enumMap["note"] = note;
    enumMap["warn"] = warn;
    enumMap["err"] = err;
    enumMap["fatal"] = fatal;
}

std::ostream& operator<< (std::ostream& strm, severity_level level) {
    static const char* strings[] = { 
      "debug", "info", "note", "warn", "err", "fatal"
    };

    if (static_cast< std::size_t >(level) < sizeof(strings) / sizeof(*strings))
        strm << strings[level];
    else
        strm << static_cast< int >(level);

    return strm;
}



void setup_logging(std::string lvl) {

  logging::core::get()->add_global_attribute(
    "ProcessID", attrs::current_process_id()
  );
  logging::core::get()->add_global_attribute(
    "Scope", attrs::named_scope()
  );

  logging::add_console_log(
    std::clog,
    keywords::format = (
      expr::stream
        //<< expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S ")
        << "("<< pid << ") "
        << "[" << severity << "] "
        << "[" << named_scope << "] "
        << expr::smessage
    )
  );

  try {
    // set the severity level...
    EnumParser<severity_level> parser;
    logging::core::get()->set_filter(
      ( severity >= parser.parseEnum(lvl) )
    );
  } catch (std::runtime_error& e) {
    std::cout << e.what() << std::endl;
    std::cout << "'" << lvl << "' is an invalid --log-level! Must be one of "
              << "[debug, info, note, warn, err, fatal]\n";
    exit(-1);
  }

}


/** Print a message for each type of log and level...*/
void test_log_and_filter_settings() {
  // print messages of each level to each global logger...
  
  BOOST_LOG_SEV(glg, debug) << "General log, debug message. A very detailed message, possibly with some internal variable data.";
  BOOST_LOG_SEV(glg, info)  << "General log, info message. A detailed operating message."; 
  BOOST_LOG_SEV(glg, note)  << "General log, note message. A general operating message."; 
  BOOST_LOG_SEV(glg, warn)  << "General Log, warn message. Something is amiss, but results should be ok."; 
  BOOST_LOG_SEV(glg, err)   << "General log, error message. The program may keep running, but results should be suspect."; 
  BOOST_LOG_SEV(glg, fatal) << "General log, fatal error message. The program cannot continue and will exit non zero."; 
}



