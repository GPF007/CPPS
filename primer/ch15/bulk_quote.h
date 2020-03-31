#include "quote.h"

class Bulk_quote:public Quote{
public:
    double net_price(std::size_t) const override;

};