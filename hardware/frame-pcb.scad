h_key = dxf_dim(file="frame-pcb.dxf", name="key",
                layer="side-view", origin=[0, 0], scale=1);
h_top_plate = dxf_dim(file="frame-pcb.dxf", name="tpl",
                      layer="side-view", origin=[0, 0], scale=1);
h_mid = dxf_dim(file="frame-pcb.dxf", name="mid",
                layer="side-view", origin=[0, 0], scale=1);
h_bottom_plate = dxf_dim(file="frame-pcb.dxf", name="bpl",
                         layer="side-view", origin=[0, 0], scale=1);
h_label_clearance = dxf_dim(file="frame-pcb.dxf", name="lbl",
                layer="side-view", origin=[0, 0], scale=1);
x0_cable = dxf_dim(file="frame-pcb.dxf", name="x0cable",
                layer="cable", origin=[0, 0], scale=1);
y0_cable = dxf_dim(file="frame-pcb.dxf", name="y0cable",
                layer="cable", origin=[0, 0], scale=1);
delta_cx = dxf_dim(file="frame-pcb.dxf", name="delta_cx",
                   layer="cable", origin=[0, 0], scale=1);
delta_cy = dxf_dim(file="frame-pcb.dxf", name="delta_cy",
                   layer="cable", origin=[0, 0], scale=1);
epsilon = 1;

difference() {
  union() {
    difference() {
      hull() {
        /* color("green") { */
        color("green", $fs = 0.2, $fa = 2) {
          rotate_extrude() {
            import (file = "frame-pcb.dxf", layer = "outline-profile");
          }
          translate([delta_cx, 0, 0]) {
            rotate_extrude() {
              import (file = "frame-pcb.dxf", layer = "outline-profile");
            }
          }
          translate([delta_cx, delta_cy, 0]) {
            rotate_extrude() {
              import (file = "frame-pcb.dxf", layer = "outline-profile");
            }
          }
          translate([0, delta_cy, 0]) {
            rotate_extrude() {
              import (file = "frame-pcb.dxf", layer = "outline-profile");
            }
          }
        }
      }
      color("red") {
        translate([0, 0, -h_bottom_plate - h_label_clearance - epsilon]) {
          linear_extrude(height = h_key + h_top_plate + h_mid + h_bottom_plate + h_label_clearance + 2 * epsilon) {
            import (file = "frame-pcb.dxf", layer = "outline");
          }
        }
      }
    }
    translate([0, 0, -h_bottom_plate]) {
      linear_extrude(height = h_bottom_plate + h_mid + h_top_plate) {
        import (file = "frame-pcb.dxf", layer = "hooks");
      }
    }
    translate([0, 0, 0]) {
      linear_extrude(height = h_mid) {
        import (file = "frame-pcb.dxf", layer = "plate-support");
      }
    }
  }
  /* color("cyan") { */
  color("cyan", $fs = 0.2, $fa = 2) {
    translate([x0_cable, y0_cable, 0]) {
      rotate([-90, 0, 0]) {
        rotate_extrude() {
          import (file = "frame-pcb.dxf", layer = "cable-shape");
        }
      }
    }
  }
  translate([delta_cx - x0_cable, y0_cable + 2, (h_label_clearance + h_bottom_plate + h_mid + h_top_plate + h_key) / 2 - (h_label_clearance + h_bottom_plate)]) {
    rotate([90, 0, 180]) {
      linear_extrude(height = 5) {
        text("ISO50", halign = "left", valign = "center", font = "DejaVu Sans:style=Bold", size = 6, spacing = 1.1);
      }
    }
  }
  translate([x0_cable, y0_cable + 15, 0]) {
    rotate([90, 0, 0]) {
      linear_extrude(height = 30) {
        import (file = "frame-pcb.dxf", layer = "cable-chamfer");
      }
    }
  }
}
