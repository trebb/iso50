echo(version=version());

h_key = dxf_dim(file="frame.dxf", name="key",
                layer="side-view", origin=[0, 0], scale=1);
h_top_plate = dxf_dim(file="frame.dxf", name="tpl",
                      layer="side-view", origin=[0, 0], scale=1);
h_mid = dxf_dim(file="frame.dxf", name="mid",
                layer="side-view", origin=[0, 0], scale=1);
h_bottom_plate = dxf_dim(file="frame.dxf", name="bpl",
                         layer="side-view", origin=[0, 0], scale=1);
h_label_clearance = dxf_dim(file="frame.dxf", name="lbl",
                layer="side-view", origin=[0, 0], scale=1);

color("red") {
  translate([0, 0, -h_bottom_plate - h_label_clearance]) {
    linear_extrude(height = h_key + h_top_plate + h_mid + h_bottom_plate + h_label_clearance) {
      import (file = "frame.dxf", layer = "outline");
    }
  }
}
color("blue") {
  translate([0, 0, -h_bottom_plate]) {
    linear_extrude(height = h_bottom_plate + h_mid + h_top_plate) {
      import (file = "frame.dxf", layer = "hooks");
    }
  }
}
color("green") {
  translate([0, 0, 0]) {
    linear_extrude(height = h_mid) {
      import (file = "frame.dxf", layer = "plate-support");
    }
  }
}
