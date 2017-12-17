#include <iostream>
#include "TestObject.h"
#include "Tree.h"
bool test_create() {
    TestObject T;
    T.Print("TEST CREATE");
    try {
        Tree<int, bool> Aye;
        T.Compare(1, "eq", 1, "Create Tree");
    }
    catch(std::exception) {
        T.Compare(0, "eq", 1, "Create Tree");
    }
    return T.Result();
}
bool test_insert() {
    TestObject T;
    T.Print("TEST INSERT");
    Tree<int, int> Aye;

    T.Compare(Aye.Insert(2, 1), "eq", 1,  "Is Insert unique 1");
    T.Compare(Aye.Insert(1, 1), "eq", 1, " Is Insert unique 2");
    T.Compare(Aye.Insert(3, 1), "eq", 1, " Is Insert unique 3");
    T.Compare(Aye.Insert(2, 1), "eq", 0, " Is Insert non-unique");
    return T.Result();
}
bool test_find() {
    TestObject T;
    T.Print("TEST FIND");
    Tree<int, int> Aye;

    Aye.Insert(2,8);
    Aye.Insert(3,7);
    Aye.Insert(1,10);

    T.Compare(Aye.Find(3)->second, "eq", 7, "Find existing check value 1");
    T.Compare(Aye.Find(2)->second, "eq", 8, "Find existing check value 2");
    T.Compare(Aye.Find(1)->second, "eq", 10, "Find existing check value 3");


    T.Compare(Aye.Find(3)->first, "eq", 3, "Find existing check key 1");
    T.Compare(Aye.Find(2)->first, "eq", 2, "Find existing check key 2");
    T.Compare(Aye.Find(1)->first, "eq", 1, "Find existing check key 3");

    T.Compare(Aye.Find(10), "eq", nullptr, "Find not existing");
    return T.Result();
}
bool test_delete_leaf() {
    TestObject T;
    T.Print("TEST DELETE LEAF");

    Tree<int, int> Aye;
    Aye.Insert(1,1);
    Aye.Insert(4,4);
    Aye.Insert(5,5);

    T.Compare(Aye.Find(1), "ne", nullptr, "Find Elem");
    T.Compare(Aye.Delete(1), "eq", 1, "Is Deleted Elem");
    T.Compare(Aye.Find(1), "eq", nullptr, "Can't Find deleted");
    return T.Result();
}
bool test_delete_root_leaf() {
    TestObject T;
    T.Print("TEST DELETE ROOT LEAF");

    Tree<int, int> Aye;
    Aye.Insert(1,1);

    T.Compare(Aye.Find(1), "ne", nullptr, "Find Elem");
    T.Compare(Aye.Delete(1), "eq", 1, "Delete Elem");
    T.Compare(Aye.Find(1), "eq", nullptr, "Can't Find deleted");
    return T.Result();
}
bool test_delete_one_kid() {
    TestObject T;
    T.Print("TEST DELETE NODE WITH ONE KID");

    Tree<int, int> Aye;
    Aye.Insert(1,1);
    Aye.Insert(4,4);
    Aye.Insert(5,5);
    Aye.Insert(8,8);

    T.Compare(Aye.Find(5), "ne", nullptr, "Find Elem");
    T.Compare(Aye.Delete(5), "eq", 1, "Delete Elem");
    T.Compare(Aye.Find(5), "eq", nullptr, "Can't Find deleted  ");
    T.Compare(Aye.Find(8), "ne", nullptr, "Find son of deleted");
    return T.Result();
}
bool test_delete_one_kid_root() {
    TestObject T;
    T.Print("TEST DELETE ROOT WITH ONE KID");

    Tree<int, int> Aye;
    Aye.Insert(1,1);
    Aye.Insert(2,2);

    T.Compare(Aye.Find(1), "ne", nullptr, "Find Elem");
    T.Compare(Aye.Delete(1), "eq", 1, "Delete Elem");
    T.Compare(Aye.Find(1), "eq", nullptr, "can't Find deleted");
    T.Compare(Aye.Find(2), "ne", nullptr, "Find son of deleted");
    return T.Result();
}
bool test_delete_two_kid() {
    TestObject T;
    T.Print("TEST DELETE NODE WITH TWO KID");

    Tree<int, int> Aye;
    Aye.Insert(1, 1);
    Aye.Insert(4, 4);
    Aye.Insert(5, 5);
    Aye.Insert(8, 8);
    Aye.Insert(3, 3);
    Aye.Insert(0, 0);

    T.Compare(Aye.Find(1), "ne", nullptr, "Find Elem");
    T.Compare(Aye.Delete(1), "eq", 1, "Delete Elem");
    T.Compare(Aye.Find(1), "eq", nullptr, "can't Find deleted");
    T.Compare(Aye.Find(0), "ne", nullptr, "Find one son");
    T.Compare(Aye.Find(3), "ne", nullptr, "Find second son");
    return T.Result();
}
bool test_delete_two_kid_root() {
    TestObject T;
    T.Print("TEST DELETE ROOT WITH TWO KID");

    Tree<int, int> Aye;
    Aye.Insert(1,1);
    Aye.Insert(2,2);
    Aye.Insert(3,3);

    T.Compare(Aye.Find(2), "ne", nullptr, "Find Elem");
    T.Compare(Aye.Delete(2), "eq", 1, "Delete Elem");
    T.Compare(Aye.Find(2), "eq", nullptr, "can't Find deleted");
    T.Compare(Aye.Find(1), "ne", nullptr, "Find one son");
    T.Compare(Aye.Find(3), "ne", nullptr, "Find second son");
    return T.Result();
}
bool test_3_delete() {
    TestObject T;
    T.Print("TEST DELETE ROOT WITH TWO KID");

    Tree<int, int> Aye;
    Aye.Insert(1,1);
    Aye.Insert(2,2);
    Aye.Insert(3,3);
    Aye.Insert(6,6);
    Aye.Insert(9,9);
    Aye.Insert(5,5);
    Aye.Insert(12,12);
    Aye.Insert(7,7);
    Aye.Insert(10,10);
    Aye.Insert(0,0);
    Aye.Insert(-2,-2);
    Aye.Insert(-8,-8);

    T.Compare(Aye.Find(2), "ne", nullptr, "Find Elem 00");
    T.Compare(Aye.Delete(2), "eq", 1, "Delete Elem 00");
    T.Compare(Aye.Find(2), "eq", nullptr, "can't Find deleted 00");

    T.Compare(Aye.Find(10), "ne", nullptr, "Find Elem 01");
    T.Compare(Aye.Delete(10), "eq", 1, "Delete Elem 01");
    T.Compare(Aye.Find(10), "eq", nullptr, "can't Find deleted 01");


    T.Compare(Aye.Find(-2), "ne", nullptr, "Find Elem 02");
    T.Compare(Aye.Delete(-2), "eq", 1, "Delete Elem 02");
    T.Compare(Aye.Find(-2), "eq", nullptr, "can't Find deleted 02");


    T.Compare(Aye.Find(1), "ne", nullptr, "Find Elem 1 3");
    T.Compare(Aye.Find(3), "ne", nullptr, "Find Elem 2");
    T.Compare(Aye.Find(6), "ne", nullptr, "Find Elem 3");
    T.Compare(Aye.Find(9), "ne", nullptr, "Find Elem 4");
    T.Compare(Aye.Find(5), "ne", nullptr, "Find Elem 5");
    T.Compare(Aye.Find(12), "ne", nullptr, "Find Elem 6");
    T.Compare(Aye.Find(7), "ne", nullptr, "Find Elem 7");
    T.Compare(Aye.Find(0), "ne", nullptr, "Find Elem 8");
    T.Compare(Aye.Find(-8), "ne", nullptr, "Find Elem 9");
    return T.Result();
}
int main() {
    std::vector< bool (*)() > vec = {&test_create, &test_insert, &test_find, &test_delete_leaf, &test_delete_root_leaf,
                                     &test_delete_one_kid, &test_delete_one_kid_root, &test_delete_two_kid, &test_delete_two_kid_root, &test_3_delete};
    test_starter(vec);
    return 0;
}