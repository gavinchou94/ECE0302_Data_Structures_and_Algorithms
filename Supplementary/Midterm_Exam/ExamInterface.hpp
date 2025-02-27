/** @file ExamInterface.hpp */
#ifndef EXAM_INTERFACE_
#define EXAM_INTERFACE_

template <typename ItemType>
class ExamInterface
{
public:
   /** Gets the current score of the exam.
   @return The score of the exam.*/
   virtual ItemType getScore() const = 0;

}; // end ExamInterface
#endif