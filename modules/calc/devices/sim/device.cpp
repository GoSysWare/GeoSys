#include "../../ioss/ddk.h"
#include "expression.h"




bool update_value(std::string tag_name, vam_t new_value)
{
    double val;


	evaluate(tag_name, &val);

}
