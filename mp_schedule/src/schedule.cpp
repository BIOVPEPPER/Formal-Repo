/**
 * @file schedule.cpp
 * Exam scheduling using graph coloring
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "schedule.h"
#include "utils.h"
#include <algorithm>

/**
 * Given a filename to a CSV-formatted text file, create a 2D vector of strings where each row
 * in the text file is a row in the V2D and each comma-separated value is stripped of whitespace
 * and stored as its own string. 
 * 
 * Your V2D should match the exact structure of the input file -- so the first row, first column
 * in the original file should be the first row, first column of the V2D.
 *  
 * @param filename The filename of a CSV-formatted text file. 
 */
V2D file_to_V2D(const std::string &filename) {
    std::ifstream file(filename);
    V2D result;
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            std::stringstream lineStream(line);
            std::string item;
            std::vector<std::string> row;

            while (std::getline(lineStream, item, ',')) {
                // Trimming leading and trailing whitespaces
                item.erase(0, item.find_first_not_of(' '));
                item.erase(item.find_last_not_of(' ') + 1);

                row.push_back(item);
            }

            result.push_back(row);
        }
    }

    return result;
}

StringMap v2dToMap(const V2D &v) {
    StringMap m;
    for (const auto &row : v) {
        if (!row.empty()) {
            m[row[0]] = std::vector<std::string>(row.begin() + 1, row.end());
        }
    }

    return m;
}


std::vector<std::string> findCommonCourses(const std::string &courseId, const StringMap &roster, const StringMap &students) {
    std::vector<std::string> commonCourses;
    commonCourses.push_back(courseId);

    for (const auto &studentId : roster.at(courseId)) {
        auto studentIt = students.find(studentId);

        if (studentIt != students.end() && std::find(studentIt->second.begin(), studentIt->second.end(), courseId) != studentIt->second.end()) {
            commonCourses.push_back(studentId);
        }
    }

    return commonCourses;
}
/**
 * Given a course roster and a list of students and their courses, 
 * perform data correction and return a course roster of valid students (and only non-empty courses).
 * 
 * A 'valid student' is a student who is both in the course roster and the student's own listing contains the course
 * A course which has no students (or all students have been removed for not being valid) should be removed
 * 
 * @param cv A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param student A 2D vector of strings where each row is a student ID followed by the courses they are taking
 */
V2D clean(const V2D &cv, const V2D &sv) {
    StringMap roster = v2dToMap(cv);
    StringMap svs = v2dToMap(sv);
    V2D rosterC;

    for (const auto &course : cv) {
        if (!course.empty()) {
            std::vector<std::string> commonCourses = findCommonCourses(course[0], roster, svs);

            if (commonCourses.size() > 1) {
                rosterC.push_back(commonCourses);
            }
        }
    }

    return rosterC;
}

/**
 * Given a collection of courses and a list of available times, create a valid scheduling (if possible).
 * 
 * A 'valid schedule' should assign each course to a timeslot in such a way that there are no conflicts for exams
 * In other words, two courses who share a student should not share an exam time.
 * Your solution should try to minimize the total number of timeslots but should not exceed the timeslots given.
 * 
 * The result V2D should have one row for each timeslot, even if that timeslot is not used.
 * 
 * As the problem is NP-complete, your first scheduling might not result in a valid match. Your solution should 
 * continue to attempt different schedulings until 1) a valid scheduling is found or 2) you have exhausted all possible
 * starting positions. If no match is possible, return a V2D with one row with the string '-1' as the only value. 
 * 
 * @param courses A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param timeslots A vector of strings giving the total number of unique timeslots
 */
V2D schedule(const V2D &courses, const std::vector<std::string> &timeslots){
    // Your code here!
    V2D result;
    return result;
}