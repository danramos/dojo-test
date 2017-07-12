#pragma once

class NetworkInterface
{
public:
   virtual int findMatch() = 0;

   virtual bool notifyMove(int move) = 0;

   virtual int getOpponentMove() = 0;

   virtual void leave() = 0;

};
