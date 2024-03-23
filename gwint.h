#ifndef GWINTSERWER_GWINT_H
#define GWINTSERWER_GWINT_H

#include <boost/function.hpp>
#include <boost/property_tree/ptree.hpp>

namespace gwint {

    using Wiadomosc = boost::property_tree::ptree;
    using OdsylaczOdpowiedzi = boost::function<void(Wiadomosc)>;

    void ruch(Wiadomosc const &, OdsylaczOdpowiedzi const &);
}

#endif //GWINTSERWER_GWINT_H
