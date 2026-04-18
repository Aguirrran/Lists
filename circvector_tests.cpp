#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "circvector.h"

using namespace std;
using namespace testing;

TEST(CircVectorCore, isContructorEmpty) {
  CircVector<int> testVector;
  EXPECT_THAT(testVector.empty(), true);
}
TEST(CircVectorCore, isSizeTheSame) {
  CircVector<int> testVector;
  EXPECT_THAT(testVector.size(), 0);
  EXPECT_THAT(testVector.size(), testVector.size());
}
TEST(CircVectorCore, pushFrontUpdateSize) {
  CircVector<int> testVector;
  testVector.push_front(5);
  testVector.push_front(10);
  EXPECT_THAT(testVector.size(), 2);
}
TEST(CircVectorCore, pushBackUpdateSize) {
  CircVector<int> testVector;
  testVector.push_back(5);
  testVector.push_back(10);
  EXPECT_THAT(testVector.size(), 2);
}
TEST(CircVectorCore, isListCleared) {
  CircVector<int> testVector;
  testVector.clear();
  EXPECT_THAT(testVector.size(), 0);
  EXPECT_THAT(testVector.empty(), true);
}
TEST(CircVectorCore, outOfBounds) {
  CircVector<int> testVector;
  testVector.push_back(5);
  testVector.push_back(10);
  EXPECT_THROW(testVector.at(2), out_of_range);
}
TEST(CircVectorCore, upperBoundCheck) {
  CircVector<int> testVector;
  testVector.push_back(10);
  EXPECT_THAT(testVector.at(0), 10);
  EXPECT_THROW(testVector.at(1), out_of_range);
}
TEST(CircVectorCore, atValueCheck) {
  CircVector<int> testVector;
  testVector.push_back(5);
  testVector.push_back(10);
  testVector.push_back(15);
  EXPECT_THAT(testVector.at(1), 10);
}
TEST(CircVectorCore, isListClearedConfirmed) {
  CircVector<int> testVector;
  testVector.push_back(5);
  testVector.push_back(10);
  testVector.push_back(15);
  EXPECT_THAT(testVector.size(), 3);
  testVector.clear();
  EXPECT_THAT(testVector.size(), 0);
  EXPECT_THAT(testVector.empty(), true);
}
TEST(CircVectorCore, isSizeUpdatedAfterPopBack) {
  CircVector<int> testVector;
  testVector.push_back(5);
  testVector.push_back(10);
  EXPECT_THAT(testVector.size(), 2);
  testVector.pop_back();
  EXPECT_THAT(testVector.size(), 1);
}
TEST(CircVectorCore, throwsCaseonPopBack) {
  CircVector<int> testVector;
  EXPECT_THAT(testVector.empty(), true);
  EXPECT_THROW(testVector.pop_back(), exception);
}
TEST(CircVectorCore, throwsCaseonPopFront) {
  CircVector<int> testVector;
  EXPECT_THAT(testVector.empty(), true);
  EXPECT_THROW(testVector.pop_front(), exception);
}
TEST(CircVectorCore, popElementOnOneCheck) {
  CircVector<int> testVector;
  testVector.push_back(5);
  EXPECT_THAT(testVector.size(), 1);
  EXPECT_THAT(testVector.empty(), false);
  testVector.pop_back();
  EXPECT_THAT(testVector.size(), 0);
  EXPECT_THAT(testVector.empty(), true);
  EXPECT_THROW(testVector.at(0), out_of_range);
}
TEST(CircVectorCore, popFrontUpdateSize) {
  CircVector<int> testVector;
  testVector.push_back(5);
  testVector.push_back(10);
  EXPECT_THAT(testVector.size(), 2);
  testVector.pop_front();
  EXPECT_THAT(testVector.size(), 1);
  EXPECT_THAT(testVector.at(0), 10);
}
TEST(CircVectorCore, pushFrontSize) {
  CircVector<int> testVector;
  testVector.push_back(5);
  EXPECT_THAT(testVector.size(), 1);
  EXPECT_THAT(testVector.at(0), 5);
}
TEST(CircVectorCore, pushBackSizeResize) {
  CircVector<int> testVector(2);
  testVector.push_back(5);
  testVector.push_back(10);
  EXPECT_THAT(testVector.size(), 2);
  EXPECT_THAT(testVector.get_capacity(), 2);
  testVector.push_back(15);
  EXPECT_THAT(testVector.get_capacity(), 4);
}
TEST(CircVectorCore, pushFrontSizeResize) {
  CircVector<int> testVector(2);
  testVector.push_front(5);
  testVector.push_front(10);
  EXPECT_THAT(testVector.size(), 2);
  EXPECT_THAT(testVector.get_capacity(), 2);
  testVector.push_front(15);
  EXPECT_THAT(testVector.get_capacity(), 4);
}
TEST(CircVectorCore, popBackWrappingCheck) {
  CircVector<int> testVector(10);
  // We are creating a vector of ints
  // we are pushing 2 elements to front and we know that are index is
  // moving backwards by 1 going by the slides so that makes are new index
  // if are capacity was 10 then makes are new front_idx = 8 and then the
  // push_backs do nothing at all because its still acting like its adding
  // size to it when in actual there it is actually not so are pushbacks
  // are becoming index 0,1,2 so 15,20,25! we expect at 0 to be 10 but its
  // not true due to thew wrapping not working porperly or buggy this is
  // true for the other buggy that deals with the wrapping aswell.
  testVector.push_front(5);
  testVector.push_front(10);
  testVector.push_back(15);
  testVector.push_back(20);
  testVector.push_back(25);
  EXPECT_THAT(testVector.at(0), 10);
  EXPECT_THAT(testVector.at(4), 25);
  testVector.pop_back();
  EXPECT_THAT(testVector.size(), 4);
  EXPECT_THAT(testVector.at(3), 20);
}
TEST(CircVectorAugmented, copyContstructorEmptyListCheck) {
  CircVector<int> testVector;
  CircVector<int> CopyTestVector(testVector);
  EXPECT_THAT(CopyTestVector.empty(), true);
}
TEST(CircVectorAugmented, copyContstructorCreationEmptyListCheck) {
  CircVector<int> testVector;
  CircVector<int> CopyTestVector(testVector);
  EXPECT_TRUE(CopyTestVector.empty());
  EXPECT_THAT(CopyTestVector.size(), 0);
  EXPECT_THROW(CopyTestVector.at(0), out_of_range);
}
TEST(CircVectorAugmented, copyContstructorCopyAllElementsCheck) {
  CircVector<int> testVector;
  testVector.push_back(5);
  testVector.push_back(10);
  testVector.push_back(15);
  testVector.push_back(20);
  CircVector<int> CopyTestVector(testVector);
  EXPECT_THAT(CopyTestVector.size(), testVector.size());
}
TEST(CircVectorAugmented, isOperatorSelfAssignmentProtected) {
  CircVector<int> testVector;
  testVector.push_back(5);
  testVector.push_back(10);
  CircVector<int>& CopyTestVector = testVector;
  testVector = CopyTestVector;
  EXPECT_THAT(testVector.size(), 2);
  EXPECT_THAT(testVector.at(0), 5);
  EXPECT_THAT(testVector.at(1), 10);
}
TEST(CircVectorAugmented, AssignDoesNotCreateEmptyList) {
  CircVector<int> testVector;
  testVector.push_back(5);
  testVector.push_back(10);
  testVector.push_back(15);
  testVector.push_back(20);
  CircVector<int> CopyTestVector;
  CopyTestVector.push_back(1);
  CopyTestVector.push_back(2);
  testVector = CopyTestVector;
  EXPECT_FALSE(CopyTestVector.empty());
  EXPECT_THAT(CopyTestVector.size(), testVector.size());
  EXPECT_THAT(CopyTestVector.at(0), testVector.at(0));
}
TEST(CircVectorAugmented, FindingAlwaysminus1Check) {
  CircVector<int> testVector;
  testVector.push_back(5);
  testVector.push_back(10);
  EXPECT_THAT(testVector.find(5), 0);
  EXPECT_THAT(testVector.find(10), 1);
}
TEST(CircVectorAugmented, FindBadBoundsCheck) {
  CircVector<int> testVector;
  testVector.push_back(5);
  testVector.push_back(10);
  testVector.push_back(15);
  EXPECT_THAT(testVector.find(5), 0);
  EXPECT_THAT(testVector.find(15), 2);
  EXPECT_THAT(testVector.find(10), 1);
}
TEST(CircVectorAugmented, toStringWrongCheck) {
  CircVector<int> testVector;
  EXPECT_THAT(testVector.to_string(), "[]");
  testVector.push_back(5);
  EXPECT_THAT(testVector.to_string(), "[5]");
  testVector.push_back(10);
  EXPECT_THAT(testVector.to_string(), "[5, 10]");
}
TEST(CircVectorAugmented, assigmentEmptyCheck) {
  CircVector<int> testVector;
  CircVector<int> CopyTestVector;
  CopyTestVector.push_back(1);
  CopyTestVector.push_back(2);
  CopyTestVector = testVector;
  EXPECT_TRUE(CopyTestVector.empty());
  EXPECT_THAT(CopyTestVector.size(), 0);
}
TEST(CircVectorAugmented, minusOneCheck) {
  CircVector<int> testVector;
  testVector.push_back(5);
  testVector.push_back(10);
  testVector.push_back(15);
  EXPECT_THAT(testVector.find(4), -1);
}
TEST(CircVectorAugmented, copyconstructorMissingElem) {
  CircVector<int> testVector;
  testVector.push_back(5);
  testVector.push_back(10);
  testVector.push_back(15);
  testVector.push_back(20);
  testVector.push_back(25);
  testVector.push_back(40);
  CircVector<int> CopyTestVector(testVector);
  EXPECT_THAT(CopyTestVector.size(), testVector.size());
  for (size_t i = 0; i < testVector.size(); i++) {
    EXPECT_THAT(CopyTestVector.at(i), testVector.at(i))
        << "Mismatch at index " << i;
  }
  EXPECT_THAT(CopyTestVector.at(0), 5);
  EXPECT_THAT(CopyTestVector.at(3), 20);
  EXPECT_THAT(CopyTestVector.at(CopyTestVector.size() - 1), 40);
}
TEST(CircVectorAugmented, assignMissingLastElem) {
  CircVector<int> testVector;
  testVector.push_back(5);
  testVector.push_back(10);
  testVector.push_back(15);
  testVector.push_back(20);
  testVector.push_back(25);
  testVector.push_back(40);
  CircVector<int> CopyTestVector;
  CopyTestVector.push_back(-1);
  CopyTestVector = testVector;
  EXPECT_THAT(CopyTestVector.size(), testVector.size());
  EXPECT_THAT(CopyTestVector.at(CopyTestVector.size() - 1), 40);
  for (size_t i = 0; i < testVector.size(); i++) {
    EXPECT_THAT(CopyTestVector.at(i), testVector.at(i)) << "Mismatch at " << i;
  }
}
TEST(CircVectorExtras, InsertBeforeLastCheck) {
  CircVector<int> testVector;
  testVector.push_back(5);
  testVector.push_back(10);
  testVector.push_back(15);
  testVector.insert_before(testVector.size() - 1, 30);
  EXPECT_THAT(testVector.size(), 4);
  EXPECT_THAT(testVector.to_string(), "[5, 10, 30, 15]");
}
TEST(CircVectorExtras, InsertBeforeNoThrowCheck) {
  CircVector<int> testVector;
  testVector.push_back(5);
  testVector.push_back(10);
  testVector.push_back(15);
  EXPECT_ANY_THROW(testVector.insert_before(4, 30));
}
TEST(CircVectorExtras, removeEveryOtherNoSizeUpdateCheck) {
  CircVector<int> testVector;
  testVector.push_back(5);
  testVector.push_back(10);
  testVector.push_back(20);
  testVector.push_back(25);
  testVector.push_back(30);
  testVector.remove_every_other();
  EXPECT_THAT(testVector.to_string(), "[5, 20, 30]");
  EXPECT_THAT(testVector.size(), 3);
}
TEST(CircVectorExtras, removeEveryOtherWrongElementCheck) {
  CircVector<int> testVector;
  EXPECT_NO_THROW(testVector.remove_every_other());
  EXPECT_THAT(testVector.size(), 0);
  EXPECT_THAT(testVector.to_string(), "[]");
  CircVector<int> testVector2;
  testVector2.push_back(10);
  testVector2.remove_every_other();
  EXPECT_THAT(testVector2.size(), 1);
  EXPECT_THAT(testVector2.to_string(), "[10]");
}
TEST(CircVectorExtras, insertBeforeResizeIsFullCheck) {
  CircVector<int> testVector(3);
  testVector.push_back(5);
  testVector.push_back(10);
  testVector.push_back(20);
  testVector.insert_before(1, 30);
  EXPECT_THAT(testVector.size(), 4);
  EXPECT_THAT(testVector.to_string(), "[5, 30, 10, 20]");
}
