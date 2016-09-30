/* 
 * File:   bstring.h
 * Author: roberto
 *
 * Created on April 15, 2014, 3:05 PM
 */

#ifndef BSTRING_H
#define BSTRING_H

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * Split a string into an array of string using the delimiter
     * 
     * @param dest the destination pointer
     * @param src the source pointer
     * @param delimiter the delimiter
     * @return a array with the splited strings
     */
    extern size_t splitString(char ***dest, char *src, const char *delimiter);

    /**
     * Return 0 if the string haystack ends with the string needle
     * 
     * @param haystack the string to be analyzed
     * @param needle the suffix string
     * @return 0 if the string haystack ends with the string needle, 1 if not
     */
    int strbcmp(const char *haystack, const char *needle);

    /**
     * Duplicate the src string until the delimiter or the newline or \0 are found
     * 
     * @param src string to duplicate
     * @param delimiter delimiter to stop duplication
     * @return string
     */
    char *strdupdel(char *src, char delimiter);

    /**
     * Count the number of occurrences of characters in c in the string str
     * 
     * @param str the string to count on
     * @param c the character to be counted ended by \0
     * @return the number of occurrences 
     */
    int countCharacter(const char *str, const char *c);

    /**
     * Create a new string with the complement sequence of input
     * 
     * @param input the sequence 
     * @return a new char * with the complement sequence
     */
    char *complement(const char *input);

    /**
     * Shuffle the string
     * 
     * @param input the input string to be shuffle 
     * @return a new char * with the shuffle string
     */
    char *shuffle(const char *input);

    /**
     * Change the string to upper characters
     * 
     * @param src the string to be changed
     */
    void toUpper(char **src);


#ifdef __cplusplus
}
#endif

#endif /* BSTRING_H */

