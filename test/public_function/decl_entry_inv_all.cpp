
// Test all derived and base classes with entry invariants.

#undef BOOST_CONTRACT_AUX_TEST_NO_A_INV
#undef BOOST_CONTRACT_AUX_TEST_NO_B_INV
#undef BOOST_CONTRACT_AUX_TEST_NO_C_INV
#include "decl.hpp"

#include <boost/detail/lightweight_test.hpp>
#include <sstream>

int main() {
    std::ostringstream ok;
    
    a aa;
    
    a_entry_inv = true;
    b_entry_inv = true;
    c_entry_inv = true;
    a_entering_inv = b_entering_inv = c_entering_inv = true;
    out.str("");
    aa.f();
    ok.str(""); ok // Test nothing failed.
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
        << "b::static_inv" << std::endl
        << "b::inv" << std::endl
        << "a::static_inv" << std::endl
        << "a::inv" << std::endl

        << "c::f::pre" << std::endl
        
        << "c::f::old" << std::endl
        << "b::f::old" << std::endl
        << "a::f::old" << std::endl
        
        << "a::f::body" << std::endl
        
        << "c::static_inv" << std::endl
        << "c::inv" << std::endl
        << "b::static_inv" << std::endl
        << "b::inv" << std::endl
        << "a::static_inv" << std::endl
        << "a::inv" << std::endl
        
        << "c::f::old" << std::endl
        << "c::f::post" << std::endl
        << "b::f::old" << std::endl
        << "b::f::post" << std::endl
        << "a::f::post" << std::endl
    ;
    BOOST_TEST(out.eq(ok.str()));
    
    struct err {};
    boost::contract::set_entry_invariant_failed(
            [] (boost::contract::from) { throw err(); });

    a_entry_inv = false;
    b_entry_inv = true;
    c_entry_inv = true;
    a_entering_inv = b_entering_inv = c_entering_inv = true;
    out.str("");
    try {
        aa.f();
        BOOST_TEST(false);
    } catch(err const&) {
        ok.str(""); ok
            << "c::static_inv" << std::endl
            << "c::inv" << std::endl
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
            << "a::static_inv" << std::endl
            << "a::inv" << std::endl // Test this failed.
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }

    a_entry_inv = true;
    b_entry_inv = false;
    c_entry_inv = true;
    a_entering_inv = b_entering_inv = c_entering_inv = true;
    out.str("");
    try {
        aa.f();
        BOOST_TEST(false);
    } catch(err const&) {
        ok.str(""); ok
            << "c::static_inv" << std::endl
            << "c::inv" << std::endl
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl // Test this failed.
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    a_entry_inv = true;
    b_entry_inv = true;
    c_entry_inv = false;
    a_entering_inv = b_entering_inv = c_entering_inv = true;
    out.str("");
    try {
        aa.f();
        BOOST_TEST(false);
    } catch(err const&) {
        ok.str(""); ok
            << "c::static_inv" << std::endl
            << "c::inv" << std::endl // Test this failed.
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    a_entry_inv = false;
    b_entry_inv = false;
    c_entry_inv = false;
    a_entering_inv = b_entering_inv = c_entering_inv = true;
    out.str("");
    try {
        aa.f();
        BOOST_TEST(false);
    } catch(err const&) {
        ok.str(""); ok
            << "c::static_inv" << std::endl
            << "c::inv" << std::endl // Test this failed (as all did).
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }

    return boost::report_errors();
}

