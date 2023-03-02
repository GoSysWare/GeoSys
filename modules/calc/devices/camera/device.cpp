#include "cyber/time/time.h"
#include "modules/calc/proto/value.pb.h"
#include "modules/calc/ioss/ddk.h"
#include "modules/calc/devices/camera/camera_component.h"



bool load(driver_t *dirver)
{
  apollo::drivers::camera::config::Config config;
  config.set_camera_dev("front");
  config.set_frame_id("frame");
  config.set_pixel_format("yuyv");
  config.set_io_method(IO_METHOD_MMAP);
  config.set_width(1048);
    apollo::cyber::common::SetProtoToASCIIFile(config,
      "/home/shuimujie/Works/GeoSys/modules/calc/ioss/device_info_out.conf");



}
bool unload()
{


}
bool start_device(device_t *device)
{
    CameraComponent *camera =  new CameraComponent;
    camera->Init(device->parameter);


    device->owner_field = camera;

}
bool stop_device(device_t *device)
{
    CameraComponent *camera =0;
    camera = (CameraComponent*) device->owner_field;
    if(!camera)
        delete camera;

    device->owner_field = 0;

}
bool write_value(device_t *device,std::string tag_name, vam_t vaule)
{
    CameraComponent *camera =0;
    camera = (CameraComponent*) device->owner_field;

}

bool update_value(device_t *device,std::string tag_name, vam_t value)
{
    CameraComponent *camera =0;
    camera = (CameraComponent*) device->owner_field;
    if(tag_name == "IMG"){
      value->mutable_v()->set_t(v_type::T_IMAGE);
      value->mutable_v()->set_img(camera->raw_image_->image);
    }else if(tag_name == "HEIGHT"){
      value->mutable_v()->set_t(v_type::T_UINT32);
      value->mutable_v()->set_ui(camera->raw_image_->height);

    }else if(tag_name == "WIDTH"){
      value->mutable_v()->set_t(v_type::T_UINT32);
      value->mutable_v()->set_ui(camera->raw_image_->width);
    }else{

    }
    value->set_tm(apollo::cyber::Time::Now().ToNanosecond());

}
