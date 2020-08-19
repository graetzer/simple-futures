////////////////////////////////////////////////////////////////////////////////
/// DISCLAIMER
///
/// Copyright 2020 ArangoDB GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is ArangoDB GmbH, Cologne, Germany
///
/// @author Simon Grätzer
////////////////////////////////////////////////////////////////////////////////

#include "Futures/Future.h"
#include <iostream>

using namespace arangodb;
using namespace arangodb::futures;

int foo(int x) {
  // do something with x
  std::cout << "foo(" << x << ")" << std::endl;
  return x + 1;
}


int main(int argc, char** argv) {

  std::cout << "making Promise" << std::endl;
  Promise<int> p;
  Future<int> f = p.getFuture();
  auto f2 = std::move(f).thenValue(&foo);
  std::cout << "Future chain made" << std::endl;

  // ... now perhaps in another event callback

  std::cout << "fulfilling Promise" << std::endl;
  p.setValue(42);
  // .get() waits for the Future to be fulfilled
  std::cout << "Promise fulfilled f2 contains" << f2.get() << std::endl;
}
