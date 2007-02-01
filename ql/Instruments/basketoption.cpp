/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2003 Neil Firth
 Copyright (C) 2000, 2001, 2002, 2003 RiskMap srl
 Copyright (C) 2007 StatPro Italia srl

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/reference/license.html>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include <ql/Instruments/basketoption.hpp>

namespace QuantLib {

    BasketOption::BasketOption(
        const BasketType basketType,
        const boost::shared_ptr<StochasticProcess>& process,
        const boost::shared_ptr<PlainVanillaPayoff>& payoff,
        const boost::shared_ptr<Exercise>& exercise,
        const boost::shared_ptr<PricingEngine>& engine)
    : MultiAssetOption(process, payoff, exercise, engine),
      basketType_(basketType) {}

    void BasketOption::setupArguments(PricingEngine::arguments* args) const {
        MultiAssetOption::setupArguments(args);

        BasketOption::arguments* arguments =
            dynamic_cast<BasketOption::arguments*>(args);
        QL_REQUIRE(arguments != 0, "wrong argument type");

        arguments->basketType = basketType_;
    }

    void BasketOption::arguments::validate() const {
        #if defined(QL_PATCH_MSVC6)
        MultiAssetOption::arguments copy = *this;
        copy.validate();
        #else
        MultiAssetOption::arguments::validate();
        #endif

    }
}

