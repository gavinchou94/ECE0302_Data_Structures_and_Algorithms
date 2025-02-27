/** @file puzzle.hpp */

class Puzzle {
    public:
        enum LabelType {A,B,C,D,E,F,G,H,EMPTY};
        LabelType get(int row, int col)
        {
            return A;
        }
};