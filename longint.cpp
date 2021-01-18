//
// Created by Amman Nega on 3/15/2019.
//
#include "longint.h"

LongInt::LongInt( const string str) { // constructor
    // if value is negative, we add the - symbol
    if(str[0] == '-') {
        digits.addFront('-');
        negative = true;
    }
    else {
        digits.addFront(str[0]);
        negative = false;
    }
    // loop adds characters from string individually to deque
    for(int i = 1; i < str.length(); i++) {
        if(str[i] == '0' || str[i] == '1' || str[i] == '2' ||
                str[i] == '3' || str[i] == '4' || str[i] == '5' ||
                str[i] == '6' || str[i] == '7' || str[i] == '8' ||
                str[i] == '9') { // accounts for all possible digits
            digits.addBack(str[i]);
        }
    }
    remove0s();
}

LongInt::LongInt( const LongInt & rhs) { // copy constructor
    digits = rhs.digits;
    negative = rhs.negative;
}

LongInt::LongInt() { // default constructor
    digits.addFront('0');
    negative = false;
}

LongInt::~LongInt() { // destructor
    digits.clear();
}

/*
 * precondition: have two LongInt objects
 * returns a LongInt representing the sum
 * of the two objects
 */
LongInt LongInt::operator+( const LongInt &rhs) const{
    LongInt ans;
    LongInt lhs;
    lhs.digits = digits;
    lhs.negative = negative;
    ans.digits.clear();
    // set new Deques to our two objects digits
    LongInt right = rhs;

    // if statement is for adding two positive numbers
    if(!negative && !rhs.negative) {
        addInts(lhs, right, ans);
        ans.negative = false;
    }
    else if(!negative && rhs.negative) {
        right.digits.removeFront();
        right.negative = false;
        if(lhs < right) { // checks if answer will be negative
            subtractInts(right, lhs, ans);
            ans.negative = true;
            ans.digits.addFront('-');
        }
        else {
            subtractInts(lhs, right, ans);
            ans.negative = false;
        }
    }
    else if(negative && !rhs.negative) {
        lhs.digits.removeFront();
        lhs.negative = false;
        if(lhs <= rhs) { // checks if answer will be negative
            subtractInts(right, lhs, ans);
            ans.negative = false;
        }
        else if(lhs > rhs){
            subtractInts(lhs, right, ans);
            ans.negative = true;
            ans.digits.addFront('-');
        }
    }
    else if(negative && rhs.negative) {
        // remove the negative symbol to make addition simpler
        right.digits.removeFront();
        lhs.digits.removeFront();
        right.negative = false;
        lhs.negative = false;
        // rest of code is exactly the same as positive + positive
        addInts(lhs, right, ans);
        ans.digits.addFront('-'); // add negative symbol back at the end
        ans.negative = true;
    }
    return ans;
}

LongInt LongInt::operator-( const LongInt &rhs) const {
    LongInt ans;
    LongInt lhs;
    lhs.digits = digits;
    lhs.negative = negative;
    ans.digits.clear();
    // set new Deques to our two objects digits
    LongInt right = rhs;

    if(!negative && !rhs.negative) {
        // must subtract larger number by smaller number
        if(lhs < rhs) {
            subtractInts(right, lhs, ans);
            ans.digits.addFront('-');
            ans.negative = true;
        }
        else {
            subtractInts(lhs, right, ans);
            ans.negative = false;
        }
    }
    else if(!negative && rhs.negative) {
        right.digits.removeFront(); // gets rid of subtraction symbol
        addInts(lhs, right, ans); // adds values as normal
        ans.negative = false;
    }
    else if(negative && !rhs.negative) { // same as negative + negative
        // remove the negative symbol to make addition simpler
        lhs.digits.removeFront();
        lhs.negative = false;
        // rest of code is exactly the same as positive + positive
        addInts(lhs, right, ans);
        ans.digits.addFront('-'); // add negative symbol back at the end
        ans.negative = true;
    }
    else if(negative && rhs.negative) {
        // remove '-' characters
        lhs.digits.removeFront();
        right.digits.removeFront();
        lhs.negative = false;
        right.negative = false;
        if(lhs <= rhs) {// negative number subtract the largest by smallest
            subtractInts(right, lhs, ans);
            ans.negative = false;
        }
        else if(lhs > rhs) {
            subtractInts(lhs, right, ans);
            ans.negative = true;
            ans.digits.addFront('-');
        }
    }
    return ans;
}

const LongInt& LongInt::operator=( const LongInt & rhs ) {
    digits = rhs.digits;
    negative = rhs.negative;
}

/*
 * precondition: have two LongInt objects
 * returns true if object is smaller than
 * the one passed in parameter, false otherwise
 */
bool LongInt::operator<( const LongInt & rhs ) const {
    // these Deques contain values we are comparing
    Deque<char> left = digits;
    Deque<char> right = rhs.digits;

    if(negative && !rhs.negative) { // if it's negative, we know it's smaller
        return true;
    }
    else if(!negative && rhs.negative) {
        return false;
    }
    else if(!negative && !rhs.negative) {
        if (left.size() < right.size()) {
            return true;
        }
        else if(left.size() > right.size()) {
            return false;
        }
        else {
            while(!left.isEmpty() && !right.isEmpty()) {
                if(left.getFront() < right.getFront()) {
                    return true;
                }
                else if(left.getFront() > right.getFront()) {
                    return false;
                }
                left.removeFront();
                right.removeFront();
            }
        }
    }
    else { // if both are negative
        if(left.size() < right.size())
            return false;
        else if(left.size() > right.size())
            return true;
        else {
            while(!left.isEmpty() && !right.isEmpty()) {
                if(left.getFront() > right.getFront()) {
                    return true;
                }
                else if(left.getFront() < right.getFront()) {
                    return false;
                }
                left.removeFront();
                right.removeFront();
            }
        }
    }
    return false;
}

/*
 * precondition: have two LongInt objects
 * returns true if lhs is less than or
 * equal to rhs, false otherwise
 */
bool LongInt::operator<=(const LongInt &rhs) const {
    LongInt lhs;
    lhs.digits = digits;
    lhs.negative = negative;
    if(lhs < rhs || lhs == rhs)
        return true;

    return false;
}

/*
 * precondition: have two LongInt objects
 * return true if lhs is greater than rhs,
 * false otherwise
 */
bool LongInt::operator>(const LongInt &rhs) const {
    // these Deques contain values we are comparing
    Deque<char> left = digits;
    Deque<char> right = rhs.digits;

    if(negative && !rhs.negative) // if it's negative, we know it's smaller
        return false;
    else if(!negative && rhs.negative) {
        return true;
    }
    else if(!negative && !rhs.negative) {
        if (left.size() > right.size())
            return true;
        else if(left.size() < right.size())
            return false;
        else {
            while(!left.isEmpty() && !right.isEmpty()) {
                if(left.getFront() > right.getFront()) {
                    return true;
                }
                else if(left.getFront() < right.getFront()) {
                    return false;
                }
                left.removeFront();
                right.removeFront();
            }
        }
    }
    else { // if both are negative
        if(left.size() < right.size())
            return true;
        else if(left.size() > right.size())
            return false;
        else {
            while(!left.isEmpty() && !right.isEmpty()) {
                if(left.getFront() < right.getFront()) {
                    return true;
                }
                else if(left.getFront() < right.getFront()) {
                    return false;
                }
                left.removeFront();
                right.removeFront();
            }
        }
    }
    return false;
}

/*
 * precondition: have two LongInt objects
 * returns true if lhs is greater than or
 * equal to rhs, false otherwise
 */
bool LongInt::operator>=( const LongInt &rhs ) const {
    LongInt lhs;
    lhs.digits = digits;
    lhs.negative = negative;

    if(lhs > rhs || lhs == rhs)
        return true;

    return false;
};

/*
 * precondition: have two LongInt objects
 * returns true if both deques contain the
 * same integer value and false otherwise
 */
bool LongInt::operator==(const LongInt &rhs) const {
    // these Deques contain values we are comparing
    Deque<char> left = digits;
    Deque<char> right = rhs.digits;

    if(left.size() != right.size())  // size must be the same
        return false;
    else if(negative != rhs.negative) // both must have the same sign
        return false;
    else { // check each value in deque for equality
        while(!left.isEmpty() && !right.isEmpty()) {
            if(left.getFront() != right.getFront()) {
                return false;
            }
            left.removeFront();
            right.removeFront();
        }
    }
    return true;
}

/*
 * precondition: have two LongInt objects
 * return true if not equivalent, false otherwise
 */
bool LongInt::operator!=( const LongInt & rhs ) const {
    // tmp variable to store lhs deque
    LongInt lhs;
    lhs.digits = digits;
    lhs.negative = negative;

    if(lhs == rhs)
        return false;
    else
        return true;
}

istream& operator>>( istream &in, LongInt &rhs) {
    string number;
    in >> number;
    rhs = LongInt(number);
    return in;
}

// outputs LongInt's digits as an integer
ostream& operator<<( ostream &out, const LongInt &rhs) {
    Deque<char> tmp = rhs.digits; // stores our Deque
    if(tmp.isEmpty()) { // as per requirements
        out << 0;
        return out;
    }
    if(rhs.negative) {
        out << '-';
        tmp.removeFront();
    }
    while(!tmp.isEmpty()) {
        out << tmp.removeFront();
    }
    return out;
}

/*
 * precondition: have two Deque's of type char
 * postcondition: finds sum of both deque's
 * and stores them in another Deque
 */
void LongInt::addInts(LongInt &lhs, LongInt &rhs, LongInt &ans) const {
    int carry = 0;
    int digit;
    char tmp;
    // while loop takes sum of Deque indices and puts them in ans
    while(!lhs.digits.isEmpty() && !rhs.digits.isEmpty()) {
        // subtract 48 due to ASCII table
        digit = ((int)lhs.digits.getBack() - 48 +
                 (int)rhs.digits.getBack() - 48 + carry) % 10;
        digit = digit + 48;
        tmp = (char) digit;
        ans.digits.addFront(tmp);
        carry = ( (int)lhs.digits.removeBack() - 48 +
                  (int)rhs.digits.removeBack() - 48 + carry) / 10;
    }
    // if statement puts remaining Deque indices in ans
    // takes remaining digits from either lhs or rhs, depends on which is larger
    if(!lhs.digits.isEmpty()) {
        while(!lhs.digits.isEmpty()) {
            digit = ((int)lhs.digits.getBack() - 48 + carry) % 10;
            carry = ((int)lhs.digits.removeBack() - 48 + carry) / 10;
            digit = digit + 48;
            tmp = (char)digit;
            ans.digits.addFront(tmp);
        }
    }
    else if(!rhs.digits.isEmpty()) {
        // must perform our last carry
        while(!rhs.digits.isEmpty()) {
            digit = ((int)rhs.digits.getBack() - 48 + carry) % 10;
            carry = ((int)rhs.digits.removeBack() - 48 + carry) / 10;
            digit = digit + 48;
            tmp = (char)digit;
            ans.digits.addFront(tmp);
        }

    }

    // perform our last carry
    carry = carry + 48;
    tmp = (char)carry;
    ans.digits.addFront(tmp);
    ans.remove0s();
}

/*
 * precondition: have two Deques of type char
 * postcondition: subtract both deques and place
 * result in another deque
 */
void LongInt::subtractInts(LongInt &lhs, LongInt &rhs, LongInt &ans) const {
    int borrow = 0;
    int digit;
    char tmp;
    // while loop subtracts from deques one node at a time
    while(!lhs.digits.isEmpty() && !rhs.digits.isEmpty()) {
        if((int)lhs.digits.getBack() - 48 >= (int)rhs.digits.getBack() - 48) {
            digit = ((int) lhs.digits.removeBack() - 48) - ((int) rhs.digits.removeBack() - 48) + borrow;
            digit = digit + 48;
            tmp = (char) digit;
            ans.digits.addFront(tmp);
            borrow = 0;
        }
        else { // add 10 or only subtract 38 from lhs
            digit = ((int)lhs.digits.removeBack() - 38) - ((int) rhs.digits.removeBack() - 48) + borrow;
            digit = digit + 48;
            borrow = -1;
            tmp = (char) digit;
            ans.digits.addFront(tmp);
        }
    }
    if(!lhs.digits.isEmpty()) {
        while(!lhs.digits.isEmpty()) {
            if(lhs.digits.getBack() == '0') {
                digit = ((int)lhs.digits.removeBack() + 10) + borrow;
                ans.digits.addFront((char) digit);
            }
            else {
                digit = (int)lhs.digits.removeBack() + borrow;
                ans.digits.addFront((char) digit);
            }
        }
    }
    else if(!rhs.digits.isEmpty()) {
        while(!rhs.digits.isEmpty()) {
            if(rhs.digits.getBack() == '0') {
                digit = ((int)rhs.digits.removeBack() + 10) + borrow;
                ans.digits.addFront((char) digit);
            }
            else {
                digit = (int)rhs.digits.removeBack() + borrow;
                ans.digits.addFront((char) digit);
            }
        }
    }
    ans.remove0s();
}

/*
 * precondition: have an object of type LongInt
 * postcondition: removes 0s placed at the beginning
 * of Deque as they are unnecessary.
 */
void LongInt::remove0s() {
    // we keep removing 0s until we reach an integer
    while(digits.getFront() == '0' || digits.getFront() == '-') {
        digits.removeFront();
    }
    // if value was 0, we need to put char back in Deque
    if(digits.isEmpty()) {
        digits.addFront('0');
        negative = false; // we know long int is 0 so it isn't negative
    }
    // put negative symbol back in
    if(negative)
        digits.addFront('-');
}
