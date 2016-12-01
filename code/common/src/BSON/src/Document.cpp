/**
 * @file Document.cpp
 * @brief Class for BSON document
 * @author Christopher Paccard
 *
 * Represent a BSON document
 *
 */

#include "../include/Document.hh"

namespace bson {
    Document::Document() :_nextInputType(bson::Document::KEY) {
    }

    Document::Document(const Document &document) {
        if (this != &document) {
            _nextInputType = document._nextInputType;
            _lastKey = document._lastKey;
            _buffer = document._buffer;
        }
    }

    Document& Document::operator=(const Document &document) {
        if (this != &document) {
            _nextInputType = document._nextInputType;
            _lastKey = document._lastKey;
            _buffer = document._buffer;
        }
        return *this;
    }

    Document::~Document() {
    }
}