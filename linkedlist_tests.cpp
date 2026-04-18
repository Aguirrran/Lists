#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "linkedlist.h"

using namespace std;
using namespace testing;

TEST(LinkedListCore, isContructorEmpty) {
  LinkedList<int> TestLinkList;
  EXPECT_THAT(TestLinkList.empty(), true);
}
TEST(LinkedListCore, isSizeTheSame) {
  LinkedList<int> TestLinkList;
  EXPECT_THAT(TestLinkList.size(), 0);
  EXPECT_THAT(TestLinkList.size(), TestLinkList.size());
}
TEST(LinkedListCore, pushFrontUpdateSize) {
  LinkedList<int> TestLinkList;
  TestLinkList.push_front(5);
  TestLinkList.push_front(10);
  EXPECT_THAT(TestLinkList.size(), 2);
}
TEST(LinkedListCore, pushBackUpdateSize) {
  LinkedList<int> TestLinkList;
  TestLinkList.push_back(5);
  TestLinkList.push_back(10);
  EXPECT_THAT(TestLinkList.size(), 2);
}
TEST(LinkedListCore, isListCleared) {
  LinkedList<int> TestLinkList;
  TestLinkList.clear();
  EXPECT_THAT(TestLinkList.size(), 0);
  EXPECT_THAT(TestLinkList.empty(), true);
}
TEST(LinkedListCore, outOfBounds) {
  LinkedList<int> TestLinkList;
  TestLinkList.push_back(5);
  TestLinkList.push_back(10);
  EXPECT_THROW(TestLinkList.at(2), out_of_range);
}
TEST(LinkedListCore, upperBoundCheck) {
  LinkedList<int> TestLinkList;
  TestLinkList.push_back(10);
  EXPECT_THAT(TestLinkList.at(0), 10);
  EXPECT_THROW(TestLinkList.at(1), out_of_range);
}
TEST(LinkedListCore, atValueCheck) {
  LinkedList<int> TestLinkList;
  TestLinkList.push_back(5);
  TestLinkList.push_back(10);
  TestLinkList.push_back(15);
  EXPECT_THAT(TestLinkList.at(1), 10);
}
TEST(LinkedListCore, isListClearedConfirmed) {
  LinkedList<int> TestLinkList;
  TestLinkList.push_back(5);
  TestLinkList.push_back(10);
  TestLinkList.push_back(15);
  EXPECT_THAT(TestLinkList.size(), 3);
  TestLinkList.clear();
  EXPECT_THAT(TestLinkList.size(), 0);
  EXPECT_THAT(TestLinkList.empty(), true);
}
TEST(LinkedListCore, isSizeUpdatedAfterPopBack) {
  LinkedList<int> TestLinkList;
  TestLinkList.push_back(5);
  TestLinkList.push_back(10);
  EXPECT_THAT(TestLinkList.size(), 2);
  TestLinkList.pop_back();
  EXPECT_THAT(TestLinkList.size(), 1);
}
TEST(LinkedListCore, throwsCaseonPopBack) {
  LinkedList<int> TestLinkList;
  EXPECT_THAT(TestLinkList.empty(), true);
  EXPECT_THROW(TestLinkList.pop_back(), exception);
}
TEST(LinkedListCore, throwsCaseonPopFront) {
  LinkedList<int> TestLinkList;
  EXPECT_THAT(TestLinkList.empty(), true);
  EXPECT_THROW(TestLinkList.pop_front(), exception);
}
TEST(LinkedListCore, popElementOnOneCheck) {
  LinkedList<int> TestLinkList;
  TestLinkList.push_back(5);
  EXPECT_THAT(TestLinkList.size(), 1);
  EXPECT_THAT(TestLinkList.empty(), false);
  TestLinkList.pop_back();
  EXPECT_THAT(TestLinkList.size(), 0);
  EXPECT_THAT(TestLinkList.empty(), true);
  EXPECT_THROW(TestLinkList.at(0), exception);
}
TEST(LinkedListAugmented, copyContstructorEmptyListCheck) {
  LinkedList<int> TestLinkList;
  LinkedList<int> CopyTestLinkList(TestLinkList);
  EXPECT_THAT(CopyTestLinkList.empty(), true);
}
TEST(LinkedListAugmented, copyContstructorCreationEmptyListCheck) {
  LinkedList<int> TestLinkList;
  LinkedList<int> CopyTestLinkList(TestLinkList);
  EXPECT_TRUE(CopyTestLinkList.empty());
  EXPECT_THAT(CopyTestLinkList.size(), 0);
  EXPECT_THROW(CopyTestLinkList.at(0), out_of_range);
}
TEST(LinkedListAugmented, copyContstructorCopyAllElementsCheck) {
  LinkedList<int> TestLinkList;
  TestLinkList.push_back(5);
  TestLinkList.push_back(10);
  TestLinkList.push_back(15);
  TestLinkList.push_back(20);
  LinkedList<int> CopyTestLinkList(TestLinkList);
  EXPECT_THAT(CopyTestLinkList.size(), TestLinkList.size());
}
TEST(LinkedListAugmented, isOperatorSelfAssignmentProtected) {
  LinkedList<int> TestLinkList;
  TestLinkList.push_back(5);
  TestLinkList.push_back(10);
  LinkedList<int>& CopyTestLinkList = TestLinkList;
  TestLinkList = CopyTestLinkList;
  EXPECT_THAT(TestLinkList.size(), 2);
  EXPECT_THAT(TestLinkList.at(0), 5);
  EXPECT_THAT(TestLinkList.at(1), 10);
}
TEST(LinkedListAugmented, AssignDoesNotCreateEmptyList) {
  LinkedList<int> TestLinkList;
  TestLinkList.push_back(5);
  TestLinkList.push_back(10);
  TestLinkList.push_back(15);
  TestLinkList.push_back(20);
  LinkedList<int> CopyTestLinkList;
  CopyTestLinkList.push_back(1);
  CopyTestLinkList.push_back(2);
  TestLinkList = CopyTestLinkList;
  EXPECT_FALSE(CopyTestLinkList.empty());
  EXPECT_THAT(CopyTestLinkList.size(), TestLinkList.size());
  EXPECT_THAT(CopyTestLinkList.at(0), TestLinkList.at(0));
}
TEST(LinkedListAugmented, FindingAlwaysminus1Check) {
  LinkedList<int> TestLinkList;
  TestLinkList.push_back(5);
  TestLinkList.push_back(10);
  EXPECT_THAT(TestLinkList.find(5), 0);
  EXPECT_THAT(TestLinkList.find(10), 1);
}
TEST(LinkedListAugmented, FindBadBoundsCheck) {
  LinkedList<int> TestLinkList;
  TestLinkList.push_back(5);
  TestLinkList.push_back(10);
  TestLinkList.push_back(15);
  EXPECT_THAT(TestLinkList.find(5), 0);
  EXPECT_THAT(TestLinkList.find(15), 2);
  EXPECT_THAT(TestLinkList.find(10), 1);
}
TEST(LinkedListAugmented, toStringWrongCheck) {
  LinkedList<int> TestLinkList;
  EXPECT_THAT(TestLinkList.to_string(), "[]");
  TestLinkList.push_back(5);
  EXPECT_THAT(TestLinkList.to_string(), "[5]");
  TestLinkList.push_back(10);
  EXPECT_THAT(TestLinkList.to_string(), "[5, 10]");
}
TEST(LinkedListAugmented, assigmentEmptyCheck) {
  LinkedList<int> TestLinkList;
  LinkedList<int> CopyTestLinkList;
  CopyTestLinkList.push_back(1);
  CopyTestLinkList.push_back(2);
  CopyTestLinkList = TestLinkList;
  EXPECT_TRUE(CopyTestLinkList.empty());
  EXPECT_THAT(CopyTestLinkList.size(), 0);
}
TEST(LinkedListAugmented, minusOneCheck) {
  LinkedList<int> TestLinkList;
  TestLinkList.push_back(5);
  TestLinkList.push_back(10);
  TestLinkList.push_back(15);
  EXPECT_THAT(TestLinkList.find(4), -1);
}
TEST(LinkedListExtras, InsertBeforeLastCheck) {
  LinkedList<int> TestLinkList;
  TestLinkList.push_back(5);
  TestLinkList.push_back(10);
  TestLinkList.push_back(15);
  TestLinkList.insert_before(TestLinkList.size() - 1, 30);
  EXPECT_THAT(TestLinkList.size(), 4);
  EXPECT_THAT(TestLinkList.to_string(), "[5, 10, 30, 15]");
}
TEST(LinkedListExtras, InsertBeforeNoThrowCheck) {
  LinkedList<int> TestLinkList;
  TestLinkList.push_back(5);
  TestLinkList.push_back(10);
  TestLinkList.push_back(15);
  EXPECT_ANY_THROW(TestLinkList.insert_before(4, 30));
}
TEST(LinkedListExtras, removeEveryOtherNoSizeUpdateCheck) {
  LinkedList<int> TestLinkList;
  TestLinkList.push_back(5);
  TestLinkList.push_back(10);
  TestLinkList.push_back(15);
  TestLinkList.push_back(20);
  TestLinkList.push_back(25);
  TestLinkList.push_back(30);
  TestLinkList.remove_every_other();
  EXPECT_THAT(TestLinkList.to_string(), "[5, 15, 25]");
  EXPECT_THAT(TestLinkList.size(), 3);
}
TEST(LinkedListExtras, removeEveryOtherWrongElementCheck) {
  LinkedList<int> TestLinkList;
  EXPECT_NO_THROW(TestLinkList.remove_every_other());
  EXPECT_THAT(TestLinkList.size(), 0);
  EXPECT_THAT(TestLinkList.to_string(), "[]");
  LinkedList<int> TestLinkList2;
  TestLinkList2.push_back(10);
  TestLinkList2.remove_every_other();
  EXPECT_THAT(TestLinkList2.size(), 1);
  EXPECT_THAT(TestLinkList2.to_string(), "[10]");
}
