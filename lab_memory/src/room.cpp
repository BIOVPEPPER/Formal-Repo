/**
 * @file room.cpp
 * Implementation of the Room class.
 */

#include <iostream>
#include "room.h"

Room::Room()
    : capacity(0), count(0), max_letters(26), letterCount(0)
{
    letters = new Letter[max_letters];
}

Room::Room(const std::string& init_name, int init_capacity)
    : name(init_name),
      capacity(init_capacity),
      count(0),
      max_letters(26),
      letterCount(0)
{
    letters = new Letter[max_letters];
}

Room::Room(const Room& other)
{
    copy(other);
}

Room& Room::operator=(const Room& other)
{
    if (this != &other && other.capacity != 0)   {
        clear();
        copy(other);
    }
    return *this;
}

Room::~Room()
{//here
    clear();
}

void Room::addLetter(const Letter& L)
//here
{   if(letters != NULL){
    letters[letterCount++] = L;
    count += L.count;
}
}

int Room::spaceRemaining()
{
    return capacity - count;
}

void Room::print(std::ostream & stream /* = std::cout */)
{
    stream << name << " (" << count << "/" << capacity << "):";
    if(letters != NULL){
    for (int L = 0; L < letterCount; L++)
        stream << " " << letters[L].letter;
    }
    stream << std::endl;
}

void Room::clear()
{//here
    if(letters != NULL){
        //mismatched
    delete[] letters;
    }
}

void Room::copy(const Room& other)
{
//here
    name = other.name;
    capacity = other.capacity;
    count = other.count;
    letterCount = other.letterCount;
    max_letters = other.max_letters;
    letters = new Letter[max_letters];
    for (int i = 0; i < letterCount; i++) {
        letters[i] = other.letters[i];
    }

}
