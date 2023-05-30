
#include "modules/calc/proto/geo.pb.h"
#include "modules/calc/proto/value.pb.h"
#include "modules/calc/proto/nav.pb.h"

#include <iostream>
#include <memory>
#include <regex>
#include <stdlib.h>
#include <vector>
#include <google/protobuf/util/json_util.h>
using namespace std;
using namespace google::protobuf;

using namespace google::protobuf::util;

static void Stringsplit(const string &str, const string &split,
                        vector<string> &res) {
  std::regex reg(split); // 匹配split
  std::sregex_token_iterator pos(str.begin(), str.end(), reg, -1);
  decltype(pos) end; // 自动推导类型
  for (; pos != end; ++pos) {
    res.push_back(pos->str());
  }
}

void split(const string &s, vector<string> &tokens,const string &delimiters = " ") {
  string::size_type lastPos = s.find_first_not_of(delimiters, 0);
  string::size_type pos = s.find_first_of(delimiters, lastPos);
  while (string::npos != pos || string::npos != lastPos) {
    tokens.emplace_back(s.substr(lastPos, pos - lastPos));
    lastPos = s.find_first_not_of(delimiters, pos);
    pos = s.find_first_of(delimiters, lastPos);
  }
}

int main() {

  value_tm value;
  value.set_tm(20230718);
  Geo::Path path;

  value.mutable_v()->mutable_any()->PackFrom(path);
  std::cout << "any :" << value.ShortDebugString()<<std::endl;


  Geo::Pose *pose = path.add_poses();
  pose->mutable_orientation()->set_x(0.21);
  pose->mutable_orientation()->set_y(0.22);
  pose->mutable_orientation()->set_z(0.23);
  pose->mutable_orientation()->set_w(0.24);
  pose->mutable_position()->set_x(0.25);
  pose->mutable_position()->set_y(0.26);
  pose->mutable_position()->set_z(0.27);

  pose = path.add_poses();
  pose->mutable_orientation()->set_x(1.21);
  pose->mutable_orientation()->set_y(1.22);
  pose->mutable_orientation()->set_z(1.23);
  pose->mutable_orientation()->set_w(1.24);
  pose->mutable_position()->set_x(1.25);
  pose->mutable_position()->set_y(1.26);
  pose->mutable_position()->set_z(1.27);




  value.set_t(v_type::T_ANY);
  value.mutable_v()->mutable_any()->PackFrom(path);
  std::cout << "any :" << value.ShortDebugString()<<std::endl;
  std::string json_result;
  JsonOptions options;

  MessageToJsonString(value,&json_result,options);
  std::cout << "json_result :" << json_result<<std::endl;

  options.add_whitespace = true;
  MessageToJsonString(value,&json_result,options);
  std::cout << "json_result :" << json_result<<std::endl;

  options.always_print_primitive_fields = true;
  MessageToJsonString(value,&json_result,options);
  std::cout << "json_result :" << json_result<<std::endl;

  options.preserve_proto_field_names = true;
  MessageToJsonString(value,&json_result,options);
  std::cout << "json_result :" << json_result<<std::endl;


  options.always_print_enums_as_ints = true;
  MessageToJsonString(value,&json_result,options);
  std::cout << "json_result :" << json_result<<std::endl;

  string type_name;
  google::protobuf::internal::ParseAnyTypeUrl(value.v().any().type_url(), &type_name);
  const Descriptor *new_descriptor =
      DescriptorPool::generated_pool()->FindMessageTypeByName(type_name);
  const Message *new_prototype =
      MessageFactory::generated_factory()->GetPrototype(new_descriptor);
  Message *any_msg = new_prototype->New();
  value.v().any().UnpackTo(any_msg);



  std::vector<std::string> string_list;
  split("poses",string_list, ".");
  const Descriptor *descriptor;
  const Reflection *reflection;
  const FieldDescriptor *field_descriptor;


    descriptor = pose->GetDescriptor();
    reflection = pose->GetReflection();

    field_descriptor = descriptor->FindFieldByName("Point.x");



  const Message *field_message = any_msg;
  // const Message *field_message = value.mutable_v()->mutable_any();

  //
  for (int i = 0; i < string_list.size(); i++) {
    descriptor = field_message->GetDescriptor();
    reflection = field_message->GetReflection();
    field_descriptor = descriptor->FindFieldByName(string_list[i]);
    if (field_descriptor->is_repeated()) {
        
      if(0 >= reflection->FieldSize(*field_message, field_descriptor)){
        std::cout << "outof range" <<std::endl;
        return 0;
      }
      field_message = &(
          reflection->GetRepeatedMessage(*field_message, field_descriptor, 0));
    } else {
      field_message =
          &(reflection->GetMessage(*field_message, field_descriptor));
    }
  }

  const Descriptor *position_msg_descriptor = field_message->GetDescriptor();
  const Reflection* position_msg_reflection = field_message->GetReflection();
  const FieldDescriptor *postion_x_descriptor =
  position_msg_descriptor->FindFieldByName("Geo.Pose.Point.x"); 
  double x =position_msg_reflection->GetDouble(*field_message,postion_x_descriptor);

  value_tm out_any;
  out_any.set_t(v_type::T_ANY);
  out_any.mutable_v()->mutable_any()->PackFrom(*field_message);

  // const Descriptor *position_msg_descriptor = poistion_msg.GetDescriptor();
  // const Reflection* position_msg_reflection = poistion_msg.GetReflection();
  // const FieldDescriptor *postion_x_descriptor =
  // position_msg_descriptor->FindFieldByName("x"); double x =
  // position_msg_reflection->GetDouble(poistion_msg,postion_x_descriptor);

  // v
  // const Descriptor *value_descriptor = value.GetDescriptor();
  // const Reflection* value_reflection = value.GetReflection();
  // const FieldDescriptor * v_field = value_descriptor->FindFieldByName("v");
  // const Message &v= value_reflection->GetMessage(value,v_field);
  // //var
  // const Descriptor *v_descriptor = v.GetDescriptor();
  // const Reflection* v_reflection = v.GetReflection();
  // const OneofDescriptor * var_field = v_descriptor->FindOneofByName("var");
  // const Message &any =
  // v_reflection->GetMessage(v,v_reflection->GetOneofFieldDescriptor(v,var_field));

  // const Descriptor *var_descriptor = var.GetDescriptor();
  // const Reflection* var_reflection = var.GetReflection();
  // const FieldDescriptor * any_field = var_descriptor->FindFieldByName("any");
  // const Message &any= var_reflection->GetMessage(value,any_field);

  // const Descriptor *any_descriptor = any.GetDescriptor();
  // const Reflection* any_reflection = any.GetReflection();

  //  const FieldDescriptor * any_type_field =
  //  any_descriptor->FindFieldByName("type_url"); const FieldDescriptor *
  //  any_value_field = any_descriptor->FindFieldByName("value");

  // string type = any_reflection->GetString(any,any_type_field);
  // string string_val = any_reflection->GetString(any,any_value_field);

  // const Descriptor * new_descriptor =
  // DescriptorPool::generated_pool()->FindMessageTypeByName("Geo.Pose"); const
  // Message * new_prototype =
  // MessageFactory::generated_factory()->GetPrototype(new_descriptor);
  //  Message * pose_msg = new_prototype->New();
  //  pose_msg->ParseFromString(string_val);

  // const Descriptor *pose_msg_descriptor = pose_msg->GetDescriptor();
  // const Reflection* pose_msg_reflection = pose_msg->GetReflection();

  // const FieldDescriptor *postion_descriptor =
  // pose_msg_descriptor->FindFieldByName("position");

  // const Message &poistion_msg =
  // pose_msg_reflection->GetMessage(*pose_msg,postion_descriptor);

  // const Descriptor *position_msg_descriptor = poistion_msg.GetDescriptor();
  // const Reflection* position_msg_reflection = poistion_msg.GetReflection();
  // const FieldDescriptor *postion_x_descriptor =
  // position_msg_descriptor->FindFieldByName("x"); double x =
  // position_msg_reflection->GetDouble(poistion_msg,postion_x_descriptor);

  // Message * pose_msg_1 = new Message();
  // pose_msg_1->ParseFromString(string_val);

  // pose_msg_descriptor = pose_msg->GetDescriptor();
  // pose_msg_reflection = pose_msg->GetReflection();

  // postion_descriptor = pose_msg_descriptor->FindFieldByName("position");

  // const Message &poistion_msg_1 =
  // pose_msg_reflection->GetMessage(*pose_msg,postion_descriptor);

  //   assert(text_field != NULL);
  // FieldDescriptor::Type type = text_field->();
  //   const FieldDescriptor* text_field = descriptor->FindFieldByName("tm");

  // assert(text_field->type() == FieldDescriptor::TYPE_STRING);
  //   assert(text_field->label() == FieldDescriptor::LABEL_OPTIONAL);
  //   const FieldDescriptor* numbers_field = descriptor->
  //                                          FindFieldByName("numbers");
  //   assert(numbers_field != NULL);
  //   assert(numbers_field->type() == FieldDescriptor::TYPE_INT32);
  //   assert(numbers_field->label() == FieldDescriptor::LABEL_REPEATED);

  //   // Parse the message.
  //   foo->ParseFromString(data);

  //   // Use the reflection interface to examine the contents.
  //   const Reflection* reflection = foo->GetReflection();
  //   assert(reflection->GetString(*foo, text_field) == "Hello World!");
  //   assert(reflection->FieldSize(*foo, numbers_field) == 3);
  //   assert(reflection->GetRepeatedInt32(*foo, numbers_field, 0) == 1);
  //   assert(reflection->GetRepeatedInt32(*foo, numbers_field, 1) == 5);
  //   assert(reflection->GetRepeatedInt32(*foo, numbers_field, 2) == 42);

  return 0;
}