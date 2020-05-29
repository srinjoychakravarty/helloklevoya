#include "helloklevoya.hpp"

void helloklevoya::addpet(uint64_t const _id, eosio::name const & _owner, eosio::name const & _pet_name, uint64_t const _age, eosio::name const & _type)
{

  // only authorized user can modify their own pet
  require_auth(_owner);
  
  // Type: custom eos table > pets_table 
  // Table Name: pets
  // 1st Param: table in current smart contract 
  // 2nd Param: scope of table is global i.e. anyone can access
  pets_table pets(get_self(), get_self().value);
  // 1st Param: payer of RAM
  // 2nd Param: lambda function which sets table entry type to pet_t
  pets.emplace(get_self(), [&](auto & entry) 
  {
    entry = pet_t(_id, _owner, _pet_name, _age, _type);
  });
}

void helloklevoya::updatepet(uint64_t const _id, eosio::name const & _owner, eosio::name const &  _pet_name, uint64_t const _age, eosio::name const & _type)
{
  pets_table pets(get_self(), get_self().value);

  // searches table for id (primary key)
  auto pet_iterator = pets.find(_id);

  // allows the actual owner of the pet to update
  require_auth(pet_iterator -> get_owner());

  // if found iterator id from pets table is passed in as additional first argument
  pets.modify(pet_iterator, get_self(), [&](auto & entry) 
  {
    entry = pet_t(_id, _owner, _pet_name, _age, _type);
  });       
}

void helloklevoya::deletepet(uint64_t const _id)
{
  pets_table pets(get_self(), get_self().value);
  auto pet_iterator = pets.find(_id);
  require_auth(pet_iterator -> get_owner());
  pets.erase(pet_iterator);
}
