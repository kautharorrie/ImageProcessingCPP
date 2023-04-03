#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "PGMimageProcessor.h"

//#define CONST /*const*/

/////////////////////////////////////////////////////////////
//testing the getComponent Count
TEST_CASE("Get component count.") {

    ORRKAU001::PGMimageProcessor pgm;
 
    std::pair<int, int> p(2,2);
    std::pair<int, int> q(1,50);
    std::pair<int, int> r(2,30);
    std::pair<int, int> s(6,10);
    std::pair<int, int> t(5,100);
    std::pair<int, int> u(2,6);
    
    std::shared_ptr<ORRKAU001::ConnectedComponent> share = std::make_shared<ORRKAU001::ConnectedComponent> ();
    share->addToVector(p);
    share->addToVector(q);
    share->addToVector(r);
    share->addToVector(s);
    share->addToVector(t);
    share->addToVector(u);
    pgm.addToVector(share);
    SECTION("Testing with 1 component")
    {
        REQUIRE(pgm.getComponentCount() == 1);
    }

    SECTION("Testing with 2 components")
    {
        std::shared_ptr<ORRKAU001::ConnectedComponent> share2 = std::make_shared<ORRKAU001::ConnectedComponent> ();
        share2->addToVector(p);
        share2->addToVector(q);
        share2->addToVector(r);
        share2->addToVector(s);
        share2->addToVector(t);
        share2->addToVector(u);
        pgm.addToVector(share2);
        REQUIRE(pgm.getComponentCount() == 2);
    }

    SECTION("Testing with 3 component")
    {
        std::shared_ptr<ORRKAU001::ConnectedComponent> com3 = std::make_shared<ORRKAU001::ConnectedComponent> ();
        com3->addToVector(p);
        com3->addToVector(q);
        com3->addToVector(r);
        com3->addToVector(s);
        com3->addToVector(t);
        com3->addToVector(u);
        pgm.addToVector(com3);
        REQUIRE(pgm.getComponentCount() == 3);
    }
    
		
    
   
}
/////////////////////////////////////////////////////////////////////
//testing the getLargest Count
TEST_CASE("Get Largest Size component.") {

    ORRKAU001::PGMimageProcessor pgm;
 
    std::pair<int, int> p(2,2);
    std::pair<int, int> q(1,50);
    std::pair<int, int> r(2,30);
    std::pair<int, int> s(6,10);
    std::pair<int, int> t(5,100);
    std::pair<int, int> u(1,8);
    std::pair<int, int> v(2,7);
    std::pair<int, int> w(2,60);

    
    std::shared_ptr<ORRKAU001::ConnectedComponent> share = std::make_shared<ORRKAU001::ConnectedComponent> ();
    share->addToVector(p);
    share->addToVector(q);
    share->addToVector(r);
    share->addToVector(s);
    share->addToVector(t);
    share->addToVector(u);
    pgm.addToVector(share);

    std::shared_ptr<ORRKAU001::ConnectedComponent> share2 = std::make_shared<ORRKAU001::ConnectedComponent> ();
        share2->addToVector(p);
        share2->addToVector(q);
        share2->addToVector(r);
        pgm.addToVector(share2);

    std::shared_ptr<ORRKAU001::ConnectedComponent> com3 = std::make_shared<ORRKAU001::ConnectedComponent> ();
        com3->addToVector(p);
        com3->addToVector(q);
        com3->addToVector(r);
        com3->addToVector(s);
        pgm.addToVector(com3);
    SECTION("Testing with 6 component")
    {
        REQUIRE(pgm.getLargestSize() == 6);
    }

    SECTION("Testing with 7 components")
    {
        std::shared_ptr<ORRKAU001::ConnectedComponent> share2 = std::make_shared<ORRKAU001::ConnectedComponent> ();
        share2->addToVector(p);
        share2->addToVector(q);
        share2->addToVector(r);
        share2->addToVector(s);
        share2->addToVector(t);
        share2->addToVector(u);
        share2->addToVector(v);
        pgm.addToVector(share2);
        REQUIRE(pgm.getLargestSize() == 7);
    }

    SECTION("Testing with 8 component")
    {
        std::shared_ptr<ORRKAU001::ConnectedComponent> com3 = std::make_shared<ORRKAU001::ConnectedComponent> ();
        com3->addToVector(p);
        com3->addToVector(q);
        com3->addToVector(r);
        com3->addToVector(s);
        com3->addToVector(t);
        com3->addToVector(u);
        com3->addToVector(v);
        com3->addToVector(w);
        
        pgm.addToVector(com3);
        REQUIRE(pgm.getLargestSize() == 8 );
    }
    
		
    
   
}
////////////////////////////////////////////////////////////
//testing the getSmallest Count
TEST_CASE("Get Smallest Size component.") {

    ORRKAU001::PGMimageProcessor pgm;
 
    std::pair<int, int> p(2,2);
    std::pair<int, int> q(1,50);
    std::pair<int, int> r(2,30);
    std::pair<int, int> s(6,10);
    std::pair<int, int> t(5,100);
    std::pair<int, int> u(1,8);
    std::pair<int, int> v(2,7);
    std::pair<int, int> w(2,60);

    
    std::shared_ptr<ORRKAU001::ConnectedComponent> share = std::make_shared<ORRKAU001::ConnectedComponent> ();
    share->addToVector(p);
    share->addToVector(p);
    pgm.addToVector(share);

    std::shared_ptr<ORRKAU001::ConnectedComponent> share2 = std::make_shared<ORRKAU001::ConnectedComponent> ();
        share2->addToVector(p);
        share2->addToVector(q);
        share2->addToVector(r);
        pgm.addToVector(share2);

    std::shared_ptr<ORRKAU001::ConnectedComponent> com3 = std::make_shared<ORRKAU001::ConnectedComponent> ();
        com3->addToVector(p);
        com3->addToVector(q);
        com3->addToVector(r);
        com3->addToVector(s);
        pgm.addToVector(com3);
    SECTION("Testing with 2 component")
    {
        REQUIRE(pgm.getLargestSize() == 6);
    }

    SECTION("Testing with 3 components")
    {
        std::shared_ptr<ORRKAU001::ConnectedComponent> com = std::make_shared<ORRKAU001::ConnectedComponent> ();
        com->addToVector(p);
        
        pgm.addToVector(com);
        REQUIRE(pgm.getLargestSize() == 1);
    }
}

TEST_CASE("Filter components by Size.") {

    ORRKAU001::PGMimageProcessor pgm;
 
    std::pair<int, int> p(2,2);
    std::pair<int, int> q(1,50);
    std::pair<int, int> r(2,30);
    std::pair<int, int> s(6,10);
    std::pair<int, int> t(5,100);
    std::pair<int, int> u(1,8);
    std::pair<int, int> v(2,7);
    std::pair<int, int> w(2,60);
   
    std::shared_ptr<ORRKAU001::ConnectedComponent> share3 = std::make_shared<ORRKAU001::ConnectedComponent> ();
    share3->addToVector(p);
    pgm.addToVector(share3);

    std::shared_ptr<ORRKAU001::ConnectedComponent> share = std::make_shared<ORRKAU001::ConnectedComponent> ();
    share->addToVector(p);
    share->addToVector(p);
    pgm.addToVector(share);

    std::shared_ptr<ORRKAU001::ConnectedComponent> share2 = std::make_shared<ORRKAU001::ConnectedComponent> ();
        share2->addToVector(p);
        share2->addToVector(q);
        share2->addToVector(r);
        pgm.addToVector(share2);

    std::shared_ptr<ORRKAU001::ConnectedComponent> com3 = std::make_shared<ORRKAU001::ConnectedComponent> ();
        com3->addToVector(p);
        com3->addToVector(q);
        com3->addToVector(r);
        com3->addToVector(s);
        pgm.addToVector(com3);

    std::shared_ptr<ORRKAU001::ConnectedComponent> com = std::make_shared<ORRKAU001::ConnectedComponent> ();
    com->addToVector(p);
    com->addToVector(p);
    com->addToVector(p);
    com->addToVector(p);
    com->addToVector(p);
    com->addToVector(p);
    com->addToVector(p);
    com->addToVector(p);
    com->addToVector(p);
    com->addToVector(p);
    com->addToVector(p);
    com->addToVector(p);
    com->addToVector(p);
    com->addToVector(p);
    com->addToVector(p);
    pgm.addToVector(com);

    SECTION("Testing with 2 component")
    {
        REQUIRE(pgm.filterComponentsBySize(1, 7) == 3);
        REQUIRE(pgm.filterComponentsBySize(0, 9) == 5);
        REQUIRE(pgm.filterComponentsBySize(1, 4) == 2);
        REQUIRE(pgm.filterComponentsBySize(3, 5) == 1);
    }
}

TEST_CASE("Testing copy assignments") {

    ORRKAU001::PGMimageProcessor pgm;
 
    std::pair<int, int> p(2,2);
    std::pair<int, int> q(1,50);
    std::pair<int, int> r(2,30);
    std::pair<int, int> s(6,10);
    std::pair<int, int> t(5,100);
    std::pair<int, int> u(1,8);
    std::pair<int, int> v(2,7);
    std::pair<int, int> w(2,60);
   
    std::shared_ptr<ORRKAU001::ConnectedComponent> share3 = std::make_shared<ORRKAU001::ConnectedComponent> ();
    share3->addToVector(p);
    pgm.addToVector(share3);

    std::shared_ptr<ORRKAU001::ConnectedComponent> share = std::make_shared<ORRKAU001::ConnectedComponent> ();
    share->addToVector(p);
    share->addToVector(p);
    pgm.addToVector(share);

    std::shared_ptr<ORRKAU001::ConnectedComponent> share2 = std::make_shared<ORRKAU001::ConnectedComponent> ();
        share2->addToVector(p);
        share2->addToVector(q);
        share2->addToVector(r);
        pgm.addToVector(share2);

    std::shared_ptr<ORRKAU001::ConnectedComponent> com3 = std::make_shared<ORRKAU001::ConnectedComponent> ();
        com3->addToVector(p);
        com3->addToVector(q);
        com3->addToVector(r);
        com3->addToVector(s);
        pgm.addToVector(com3);

    std::shared_ptr<ORRKAU001::ConnectedComponent> com = std::make_shared<ORRKAU001::ConnectedComponent> ();
    com->addToVector(p);
    com->addToVector(p);
    com->addToVector(p);
    com->addToVector(p);
    com->addToVector(p);
    pgm.addToVector(com);

    ORRKAU001::PGMimageProcessor a = pgm;
    ORRKAU001::PGMimageProcessor b = pgm;
    ORRKAU001::PGMimageProcessor c = pgm;
    ORRKAU001::PGMimageProcessor d = pgm;

        REQUIRE(a.getComponentCount() == pgm.getComponentCount());
        REQUIRE(b.getComponentCount() == pgm.getComponentCount());
        REQUIRE(c.getComponentCount() == pgm.getComponentCount());
        REQUIRE(d.getComponentCount() == pgm.getComponentCount());
    
}

TEST_CASE("Testing getHeight method") 
{

    ORRKAU001::PGMimageProcessor pgm;
    SECTION("Set height to 20")
    {
        pgm.setHeight(20);
        REQUIRE(pgm.getHeight() == 20);
    }
    SECTION("Set height to 10")
    {
        pgm.setHeight(10);
        REQUIRE(pgm.getHeight() == 10);
    }
    SECTION("Set height to 5")
    {
        pgm.setHeight(5);
        REQUIRE(pgm.getHeight() == 5);
    }
}

TEST_CASE("Testing setWidth method") 
{

    ORRKAU001::PGMimageProcessor pgm;
    SECTION("Set width to 20")
    {
        pgm.setWidth(20);
        REQUIRE(pgm.getWidth() == 20);
    }
    SECTION("Set width to 10")
    {
        pgm.setWidth(10);
        REQUIRE(pgm.getWidth() == 10);
    }
    SECTION("Set width to 5")
    {
        pgm.setWidth(5);
        REQUIRE(pgm.getWidth() == 5);
    }
}



