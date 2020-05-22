#include <helloklevoya.hpp>

void helloklevoya::hi(eosio::name const & nm)
{
  eosio::print("Hello ", nm);
}