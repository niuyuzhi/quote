//
//  quote.h
//  quote
//
//  Copyright (C) 2013, 2014  André Pereira Henriques
//  aphenriques (at) outlook (dot) com
//
//  This file is part of quote.
//
//  quote is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  quote is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with quote.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef quote_quote_h
#define quote_quote_h

#include <initializer_list>
#include <string>
#include <vector>
#include "conversion.h"
#include "core.h"
#include <initializer_list>
#include "MultipleInheritancePack.h"
#include "QuoteType.h"
#include "QuoteTypeWrapper.h"
#include "RangeType.h"

// For the folowwing functions: an exception is thrown if the required data can not be obtained.
namespace quote {
    inline std::string getLatestQuotesCsv(const std::string &instruments, std::vector<QuoteType> quoteTypes);
    
    inline std::string getLatestQuotesCsv(const std::string &instruments, std::initializer_list<QuoteType> quoteTypes);
    
    template<QuoteType ...quoteTypes>
    inline std::string getLatestQuotesCsv(const std::string &instruments);
    
    std::string getHistoricalQuotesCsv(const std::string &instrument, unsigned startYear, unsigned startMonth, unsigned startDay, unsigned endYear, unsigned endMonth, unsigned endDay, RangeType rangeType);
    
    //--
    
    inline std::string getLatestQuotesCsv(const std::string &instruments, std::vector<QuoteType> quoteTypes) {
        return detail::core::getLatestQuotesCsv(instruments, quoteTypes);
    }
    
    inline std::string getLatestQuotesCsv(const std::string &instruments, std::initializer_list<QuoteType> quoteTypes) {
        return detail::core::getLatestQuotesCsv(instruments, quoteTypes);
    }
    
    template<QuoteType ...quoteTypes>
    inline std::string getLatestQuotesCsv(const std::string &instruments) {
        static_assert(sizeof...(quoteTypes) != 0, "at least one quoteType should be provided");
        // check if quote types arguments are unique
        detail::MultipleInheritancePack<detail::QuoteTypeWrapper<quoteTypes>...>();
        return detail::core::getLatestQuotesCsv<std::initializer_list<QuoteType>>(instruments, {quoteTypes...});
    }
}

#endif
