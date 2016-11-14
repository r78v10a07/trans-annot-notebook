/* 
 * File:   NotFoundException.h
 * Author: veraalva
 *
 * Created on March 17, 2016, 2:27 PM
 */

#ifndef NOTFOUNDEXCEPTION_H
#define NOTFOUNDEXCEPTION_H

namespace exceptions {

    class NotFoundException : public std::exception {
    public:

        explicit NotFoundException(const char* message) : msg(message) {
        }

        explicit NotFoundException(const std::string& message) : msg(message) {
        }

        virtual ~NotFoundException(){}

        virtual const char* what() const throw () {
            return msg.c_str();
        }

    private:
        std::string msg;
    };
    
    class FileFoundException : public std::exception {
    public:

        explicit FileFoundException(const char* message) : msg(message) {
        }

        explicit FileFoundException(const std::string& message) : msg(message) {
        }

        virtual ~FileFoundException() {
        }

        virtual const char* what() const throw () {
            return msg.c_str();
        }

    private:
        std::string msg;
    };

}

#endif /* NOTFOUNDEXCEPTION_H */

