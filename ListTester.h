/* ListTester.h declares the test-class for class List.
 * Joel Adams, for CS 112 at Calvin College.
 * Lorrayya Williams and Andrew Baker
 */

#ifndef LISTTESTER_H_
#define LISTTESTER_H_

class ListTester {
public:
	void runTests();
	void testDefaultConstructor();
	void testNodeDefaultConstructor();
	void testNodeExplicitConstructor();
	void testAppend();
	void testDestructor();
	void testCopyConstructor();
	void testAssignment();
	void testInequality();
	void testWriteToStream();
	void testReadFromString();
	void testGetIndexOf();
	void testRemove();
	void testEquality();
	void testReadFromStream();
	void testWriteToString();
	void testPrepend();
	void testInsert();
	void testinsertAfter();
	void testinsertBefore();
	void testOutputoperation();

};

#endif /*LISTTESTER_H_*/
