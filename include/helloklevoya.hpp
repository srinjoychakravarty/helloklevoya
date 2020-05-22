#ifndef HELLOKLEVOYA
#define HELLOKLEVOYA

#include <eosio/eosio.hpp>
#include <pet.hpp>

CONTRACT helloklevoya : public eosio::contract
{
  public:
    using eosio::contract::contract;
    ACTION hi(eosio::name const & nm);
};
#endif