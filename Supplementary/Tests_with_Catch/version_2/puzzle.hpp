/** @file puzzle.hpp */

class Puzzle {
    public:
        enum LabelType {A,B,C,D,E,F,G,H,EMPTY};
        LabelType get(int row, int col)
        {
            return A;
        }

        void move(int from_row, int from_col, int to_row, int to_col)
        {
        // do nothing
        }

};