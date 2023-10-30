#include <boost/algorithm/string.hpp>
#include <boost/python.hpp>
#include <iostream>

namespace {
void println(std::string const &s)
{
    std::cout << s << '\n';
}

std::string to_upper(std::string const &s)
{
    return boost::to_upper_copy<std::string>(s);
}
}    // namespace

BOOST_PYTHON_MODULE(simple)
{
    namespace python = boost::python;
    python::def("println", println);
    python::def("to_upper", to_upper);
}
