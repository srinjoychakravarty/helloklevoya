#ifndef HELLOKLEVOYA
#define HELLOKLEVOYA

#include <eosio/eosio.hpp>
#include <pet.hpp>

CONTRACT helloklevoya : public eosio::contract
{
  public:
    using eosio::contract::contract;
    ACTION hi(eosio::name const & nm);
    ACTION addpet(uint64_t const _id, 
                  eosio::name const & _owner, 
                  eosio::name const &  _pet_name, 
                  uint64_t const _age, 
                  eosio::name const & _type);
};
#endif