#pragma once

static unsigned int getId () {
  static unsigned int id = 1;
  return id++;
}
