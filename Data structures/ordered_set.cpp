using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
//find_by_order() The first returns an iterator to the k-th largest element (counting from zero)
//order_of_key() the number of items in a set that are strictly smaller than our item

unordered_map<int,int>mp;
mp.reserve(1024);
mp.max_load_factor(0.25);