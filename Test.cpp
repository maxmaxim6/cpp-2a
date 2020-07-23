#include "doctest.h"
#include "FamilyTree.hpp"
using namespace family;
using namespace std;

TEST_CASE("Yosef`s Family")
{
    Tree yosef("Yosef"); 
	yosef.addFather("Yosef", "Yaakov") 
	.addMother("Yosef", "Rachel")  
	.addFather("Yaakov", "Isaac")
	.addMother("Yaakov", "Rivka")
	.addFather("Isaac", "Avraham")
	.addFather("Avraham", "Terah")
	.addMother("Isaac","Sarah");

    /*---relation method---*/
    CHECK(yosef.relation("Yosef") == string("me"));
    CHECK(yosef.relation("Rachel") == string("mother"));
    CHECK(yosef.relation("Yaakov") == string("father"));
    CHECK(yosef.relation("Rivka") == string("grandmother"));
    CHECK(yosef.relation("Isaac") == string("grandfather"));
    CHECK(yosef.relation("Avraham") == string("great-grandfather"));
    CHECK(yosef.relation("Sarah") == string("great-grandmother"));
    CHECK(yosef.relation("Terah") == string("great-great-grandfather"));
    CHECK(yosef.relation("Lavan") == string("unrelated"));
    CHECK(yosef.relation("pharoa") == string("unrelated"));


    /*---find method---*/
    CHECK(yosef.find("me") == string("Yosef"));
    CHECK(yosef.find("mother") == string("Rachel"));
    CHECK(yosef.find("father") == string("Yaakov"));
    CHECK(yosef.find("grandmother") == string("Rivka"));
    CHECK(yosef.find("grandfather") == string("Isaac"));
    CHECK(yosef.find("great-grandfather") == string("Avraham"));
    CHECK(yosef.find("great-grandmother") == string("Sarah"));
    CHECK(yosef.find("great-great-grandfather") == string("Terah"));
    /*---exceptions---*/
    try //checks the option to find not supported relation
    {
        CHECK_THROWS(yosef.find("saba"));
    }
    catch(const std::exception& e)
    {
        CHECK(e.what() == string("The tree cannot handle the 'saba' relation"));
    }
    /*---remove method---*/
    yosef.remove("Rachel");
    CHECK(yosef.relation("Rachel") == string("unrelated"));
    try // try to search for root`s mother when there is no such
    {
        CHECK_THROWS(yosef.find("mother"));
    }
    catch(const std::exception& e)
    {
        CHECK(e.what() == string("invalid relation - Yosef does`nt have a mother"));
    }
    try //try to input wrong root name
    {
        CHECK_THROWS(yosef.addFather("Yozef","bla"));
    }
    catch(const std::exception& e)
    {
        CHECK(e.what() == string("what():  invalid root name"));
    }
}
TEST_CASE("Nuni`s Family")
{
    Tree Nuni("Nuni"); 
	Nuni.addFather("Nuni", "Aharon")
	.addMother("Nuni", "Aviva")  
	.addFather("Aharon", "Shlomo")
	.addMother("Aharon", "Shoshana")
	.addFather("Aviva", "Yssachar")
	.addMother("Aviva", "Leah")
	.addFather("Shlomo", "Shalom")
    .addMother("Shlomo", "Malka")
    .addFather("Yssachar", "Yaakov")
    .addMother("Yssachar", "Dana")
    .addFather("Leah", "Ben")
    .addMother("Leah", "Rivka")
    .addFather("Shalom", "Avihai")
    .addFather("Avihai", "Tal");

    /*---relation method---*/
    CHECK(Nuni.relation("Nuni") == string("me"));
    CHECK(Nuni.relation("Aviva") == string("mother"));
    CHECK(Nuni.relation("Aharon") == string("father"));
    CHECK(Nuni.relation("Shoshana") == string("grandmother"));
    CHECK(Nuni.relation("Leah") == string("grandmother"));
    CHECK(Nuni.relation("Yssachar") == string("grandfather"));
    CHECK(Nuni.relation("Shlomo") == string("grandfather"));
    CHECK(Nuni.relation("Shalom") == string("great-grandfather"));
    CHECK(Nuni.relation("Yaakov") == string("great-grandfather"));
    CHECK(Nuni.relation("Ben") == string("great-grandfather"));
    CHECK(Nuni.relation("Malka") == string("great-grandmother"));
    CHECK(Nuni.relation("Dana") == string("great-grandmother"));
    CHECK(Nuni.relation("Rivka") == string("great-grandmother"));
    CHECK(Nuni.relation("Avihai") == string("great-great-grandfather"));
    CHECK(Nuni.relation("Tal") == string("great-great-great-grandfather"));
    CHECK(Nuni.relation("Dani") == string("unrelated"));
    CHECK(Nuni.relation("xyz") == string("unrelated"));

    /*---find method---*/
    CHECK(Nuni.find("me") == string("Nuni"));
    CHECK(Nuni.find("mother") == string("Aviva"));
    CHECK(Nuni.find("father") == string("Aharon"));
    CHECK(Nuni.find("grandmother") == string("Shoshana"));
    CHECK(Nuni.find("grandfather") == string("Shlomo"));
    CHECK(Nuni.find("great-grandfather") == string("Yaakov"));
    CHECK(Nuni.find("great-grandmother") == string("Dana"));
    CHECK(Nuni.find("great-great-grandfather") == string("Avihai"));
    CHECK(Nuni.find("great-great-great-grandfather") == string("Tal"));
    /*---exceptions---*/
    try //checks the option to find not supported relation
    {
        CHECK_THROWS(Nuni.find("sister"));
    }
    catch(const std::exception& e)
    {
        cerr << e.what() << '\n';
        CHECK(e.what() == string("The tree cannot handle the 'sister' relation"));
    }
    /*---remove method---*/
    Nuni.remove("Aviva");
    Nuni.remove("Shoshana");
    CHECK(Nuni.relation("Aviva") == string("unrelated"));
    CHECK(Nuni.relation("Ben") == string("unrelated"));
    CHECK(Nuni.relation("Yssachar") == string("unrelated"));
    CHECK(Nuni.relation("Yaakov") == string("unrelated"));
    CHECK(Nuni.relation("Dana") == string("unrelated"));
    CHECK(Nuni.relation("Rivka") == string("unrelated"));
    CHECK(Nuni.relation("Leah") == string("unrelated"));
    try // try to search for invalid relation
    {
        CHECK_THROWS(Nuni.find("mother"));
        CHECK_THROWS(Nuni.find("grandmother"));
    }
    catch(const std::exception& e)
    {
        CHECK(e.what() == string("invalid relation - Nuni does`nt have a mother"));
    }
    try //try to input wrong root name
    {
        CHECK_THROWS(Nuni.addFather("Yosef","bla"));
    }
    catch(const std::exception& e)
    {
        CHECK(e.what() == string("what():  invalid root name"));
    }


}
TEST_CASE("Dan`s family")
{
    Tree Dan("Dan"); 
	Dan.addFather("Dan", "David")
	.addMother("David", "Sasha")
	.addFather("David", "Asaf")
    .addMother("Asaf", "Laura")
	.addFather("Asaf", "Alon")
    .addMother("Alon", "Dorit")
    .addFather("Alon", "Bentzi")
	.addMother("Dan", "Lisa")  
	.addMother("Lisa", "Alice")
	.addFather("Lisa", "Jacob")
    .addFather("Jacob", "Yuri")
    .addFather("Yuri", "Alex")
    .addFather("Alex", "Boris")
    .addMother("Boris", "Johana")
    .addFather("Johana", "Bruce");

    /*---relation method---*/
    CHECK(Dan.relation("Dan") == string("me"));
    CHECK(Dan.relation("Lisa") == string("mother"));
    CHECK(Dan.relation("David") == string("father"));
    CHECK(Dan.relation("Alice") == string("grandmother"));
    CHECK(Dan.relation("Sasha") == string("grandmother"));
    CHECK(Dan.relation("Jacob") == string("grandfather"));
    CHECK(Dan.relation("Asaf") == string("grandfather"));
    CHECK(Dan.relation("Yuri") == string("great-grandfather"));
    CHECK(Dan.relation("Alon") == string("great-grandfather"));
    CHECK(Dan.relation("Laura") == string("great-grandmother"));
    CHECK(Dan.relation("Alex") == string("great-great-grandfather"));
    CHECK(Dan.relation("Dorit") == string("great-great-grandmother"));
    CHECK(Dan.relation("Bentzi") == string("great-great-grandfather"));
    CHECK(Dan.relation("Boris") == string("great-great-great-grandfather"));
    CHECK(Dan.relation("Johana") == string("great-great-great-great-grandmother"));
    CHECK(Dan.relation("Bruce") == string("great-great-great-great-great-grandfather"));
    CHECK(Dan.relation("Dani") == string("unrelated"));
    CHECK(Dan.relation("Yosef") == string("unrelated"));

        /*---find method---*/
    CHECK(Dan.find("me") == string("Dan"));
    CHECK(Dan.find("mother") == string("Lisa"));
    CHECK(Dan.find("father") == string("David"));
    CHECK(Dan.find("grandmother") == string("Sasha"));
    CHECK(Dan.find("grandfather") == string("Asaf"));
    CHECK(Dan.find("great-grandfather") == string("Yuri"));
    CHECK(Dan.find("great-grandmother") == string("Laura"));
    CHECK(Dan.find("great-great-grandfather") == string("Alex"));
    CHECK(Dan.find("great-great-grandmother") == string("Dorit"));
    CHECK(Dan.find("great-great-great-grandfather") == string("Boris"));
    CHECK(Dan.find("great-great-great-great-grandmother") == string("Johana"));
    CHECK(Dan.find("great-great-great-great-great-grandfather") == string("Bruce"));
    
    /*---exceptions---*/
    try //checks the option to find not supported relation
    {
        CHECK_THROWS(Dan.find("brother"));
    }
    catch(const std::exception& e)
    {
        CHECK(e.what() == string("The tree cannot handle the 'brother' relation"));
    }
    try //checks the option to find not supported relation
    {
        CHECK_THROWS(Dan.find("great-grandFather"));
    }
    catch(const std::exception& e)
    {
        CHECK(e.what() == string("The tree cannot handle the 'great-grandFather' relation"));
    }
    /*---remove method---*/
    Dan.remove("David");
    CHECK_THROWS(Dan.remove("David"));
    CHECK(Dan.relation("Asaf") == string("unrelated"));
    CHECK(Dan.relation("Sasha") == string("unrelated"));
    CHECK(Dan.relation("Alon") == string("unrelated"));
    CHECK(Dan.relation("Dorit") == string("unrelated"));
    CHECK(Dan.relation("Bentzi") == string("unrelated"));
    try // try to search for invalid relation
    {
        CHECK_THROWS(Dan.find("father"));
        CHECK_THROWS(Dan.find("great-great-grandmother"));
    }
    catch(const std::exception& e)
    {
        CHECK(e.what() == string("invalid relation - Dan does`nt have a father"));
    }
    try //try to input wrong root name
    {
        CHECK_THROWS(Dan.addFather("dany","bla"));
        CHECK_THROWS(Dan.addMother("dann","Lauren"));
    }
    catch(const std::exception& e)
    {
        CHECK(e.what() == string("what():  invalid root name"));
    }

}