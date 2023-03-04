#include "cyber/time/time.h"
#include "modules/calc/devices/camera/camera_component.h"
#include "modules/calc/ioss/ddk.h"
#include "modules/calc/proto/value.pb.h"

bool load(driver_t *dirver) {}
bool unload() {}
bool start_device(device_t *device) {
  CameraComponent *camera = new CameraComponent;
  camera->Init(device->parameter);

  device->owner_field = camera;
}
bool stop_device(device_t *device) {
  CameraComponent *camera = 0;
  camera = (CameraComponent *)device->owner_field;
  if (!camera)
    delete camera;

  device->owner_field = 0;
}
bool write_value(device_t *device, std::string tag_name, vam_t vaule) {
  CameraComponent *camera = 0;
  camera = (CameraComponent *)device->owner_field;
}

bool update_value(device_t *device, std::string tag_name, vam_t value) {
  CameraComponent *camera = 0;
  camera = (CameraComponent *)device->owner_field;
  if (tag_name == "IMG") {
    value->mutable_v()->set_t(v_type::T_IMAGE);
    value->mutable_v()->set_img(camera->raw_image_->image);
  } else if (tag_name == "HEIGHT") {
    value->mutable_v()->set_ui(camera->raw_image_->height);
  } else if (tag_name == "WIDTH") {
    value->mutable_v()->set_ui(camera->raw_image_->width);
  } else if (tag_name == "ISNEW") {
    value->mutable_v()->set_b(camera->raw_image_->is_new == 1 ? true : false);
  } else if (tag_name == "SEC") {
    value->mutable_v()->set_ui(camera->raw_image_->tv_sec);
  } else if (tag_name == "USEC") {
    value->mutable_v()->set_ui(camera->raw_image_->tv_usec);

  } else {
  }
  value->set_tm(apollo::cyber::Time::Now().ToNanosecond());
}
