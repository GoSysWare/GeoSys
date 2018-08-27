#ifndef NIC_CALC_IDMAP_H
#define NIC_CALC_IDMAP_H
#include <map>
#include "precomp.h"

class CdbidMap
{
public:
    CdbidMap();
    nicInt32 Add(nicUInt32 dbid, nicUInt32 localid);
    nicInt32 Del(nicUInt32 dbid);
    nicInt32 Find(nicUInt32 dbid);
    nicUInt32 GetSize();
    nicBool IsExistKey(nicUInt32 externID);

    ~CdbidMap();
private:
    std::map<nicUInt32, nicUInt32> *dbidMap_;

};
#endif // NIC_CALC_IDMAP_H
