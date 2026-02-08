#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>//max_element
#include <cstdlib>
#include <cmath>//ceil


int find_root_byBS(int n = 36){
    int l =0,r = n/2,m,ans;
    while(l<=r){
        m = (l+r)/2;
        if(m*m<=n){
            ans = m;
            l=m+1;
        }else{
            r = m-1;
        }
    }
    return ans;
}

int check_root(int n =4,int m=69){
    int low = 1,high = m , mid;
    while(low<=high){
        mid = (low + high)/2;
        int ans = mid;
        for(int _=1 ; _<n;_++){
            ans *=mid;
        }
        if(ans==m)return mid;
        else if(ans <m)low = mid +1;
        else high=mid-1;
    }
    return -1;
}

int koko_prob(std::vector<int> piles = {873375536,395271806,617254718,970525912,634754347,824202576,694181619,20191396,886462834,442389139,572655464,438946009,791566709,776244944,694340852,419438893,784015530,588954527,282060288,269101141,499386849,846936808,92389214,385055341,56742915,803341674,837907634,728867715,20958651,167651719,345626668,701905050,932332403,572486583,603363649,967330688,484233747,859566856,446838995,375409782,220949961,72860128,998899684,615754807,383344277,36322529,154308670,335291837,927055440,28020467,558059248,999492426,991026255,30205761,884639109,61689648,742973721,395173120,38459914,705636911,30019578,968014413,126489328,738983100,793184186,871576545,768870427,955396670,328003949,786890382,450361695,994581348,158169007,309034664,388541713,142633427,390169457,161995664,906356894,379954831,448138536} ,const  int total_hours = 943223529){

    long long low = 1 ,speed , hour_needed;
    
    // still O[n] returns ptr hence derefrencing it 
    long long high = *std::max_element(piles.begin(),piles.end());

    //gives reference to the local function hence can use local var
    auto needed_hrs = [&](const long long hourly) {
        long long hour_passed =0;
        for(const int &pile :piles){
            hour_passed += (pile + hourly - 1) / hourly;
        }
        return hour_passed;
    };

    while(low<=high){
        speed = (low+high)/2;
        hour_needed = needed_hrs(speed);
        if(hour_needed <=total_hours)high=speed-1;
        else low = speed+1;
    }
    //never -1 gonna happen but still 
    return static_cast<int>(low);
}



//very imp O[mlogn]
int min_days_bouquets(std::vector<int> bloomDaysheet ={1,10,3,10,2}, int n_bouquets =3, int n_flowers=1){
//NOTE : only adjacent flowers should make an bouquet
    int n = bloomDaysheet.size();
    if (n_bouquets*n_flowers > n )return -1;

    auto can_be_made = [&](int day){
        int count = 0;  // consecutive flowers that bloomed by 'day'
        int bouquets = 0;

        for (const int bloomday :bloomDaysheet)
        {
            if(bloomday <=day){
                count++;
                if(count ==n_flowers){
                    bouquets++;
                    count =0;
                }
            }else{
                count=0;
            }
            if(bouquets==n_bouquets)return true;
        }
        
        return false;
    };
    // 2*O[m]
    int l = *std::min_element(bloomDaysheet.begin(),bloomDaysheet.end());
    int r = *std::max_element(bloomDaysheet.begin(),bloomDaysheet.end());
    int mid;
    while(l<=r){
        mid = (l+r)/2;
        bool MadeBK = can_be_made(mid);
        if(MadeBK){
            r = mid-1;
        }else{
            l = mid+1;
        }
        
    }

    return l;
}

int smallestDivisorlmt(const std::vector<int> nums = {8,4,2,3},const int threshold = 10){

    //O[n=range of arr]
    auto getDivisorCeil = [&](int div){
        int sum =0;

        for(int nu :nums){
            sum += std::ceil((float)nu/div);
        }
        return sum;
    };
    int low = 1;//maybe agar lower value na le toh ans aa skata hai but we are said to fing min [if test case is Greater than range]
    int high = *std::max_element(nums.begin(),nums.end());
    int mid , ans;

    while(low<=high){
        mid = (low+high)/2;
        ans = getDivisorCeil(mid);
        std::cout<<mid<<":"<<ans<<"\n";
        if(ans <=threshold){
            high = mid-1;
        }else{
            low = mid+1;
        }
    }
    return low;
}

int cargoPackages(std::vector<int> weight ={1,2,3,1,1},int days=4){
    //since we need to find cargo capacity to fullfill shipment in days, we need atleast capacity = max_element weight
    int low = *std::max_element(weight.begin(),weight.end());
    //high as sum of all elemnets lets just say if we need to deliver in one day we nee capacity of entire arr wieghts

    int high = 0;
    for(const int& wg: weight){
        high+=wg;
    }

    int mid;


    auto dayToDeliver = [&](int cap){
        //ye func me alag se koi bhui logic laga sakte hai , like npointers , randomized sequnce , sum 
        //GOODTHING is that we can only select adjacent objects so its simpler
        int day=1;//assuming first day
        int currWg = 0;
        for(const int& wg :weight){
            if(currWg +wg > cap){
                day++;
                currWg = wg;
            }else{
                currWg +=wg;
            }
        }
        return day;
    };

    while(low<=high){
        mid = (low+high)/2;
        std::cout<<mid<<":"<<dayToDeliver(mid)<<"\n";
        //if daystodeliver less means capacity is more , since we need to converge this , we decrease capacity till the point that days to dilver is equal to target deadline
        if(dayToDeliver(mid) <= days){
            high = mid-1;
        }else{
            low = mid+1;
        }
    }
    return low;
}

int missingKElement(std::vector<int> nums={2,3,4,7,11},int k=5){
    int low=0,high =nums.size()-1,mid,ans;

    while(low<=high){
        mid = (low+high)/2;
        ans = nums[mid]-(mid+1);//this tells numbers missing from 1 starting if nums[mid]=2 and (mid+1)=2 means there is no missing no
        if(ans >= k){
            high = mid-1;
        }else{
            low = mid+1;
        }
    }
    return k+low;
}
int aggresiveCows(std::vector<int> nums = {0,3,4,7,10,9}, int k = 4){

    
    if(k>nums.size())return -1;
    
    //sorting the array
    std::sort(nums.begin(),nums.end());

    int l = 1;
    int r = nums.back() - nums.front();
    int m , ans;


    auto canStay = [&](int min){
        int count = 1;
        //agar first me fix kiye toh 
        int lastPos = nums[0];
        for(int i = 1 ;i<nums.size();i++){
            if(nums[i]-lastPos >= min){
                count++;
                lastPos = nums[i];
            }
            if(count>=k)return true;
        }
        return false;
    };

    while(l<=r){
        m=(l+r)/2;
        if(canStay(m)){
            ans = m;
            l=m+1;
        }else{
            r=m-1;
        }
    }
    return ans;
}
int minSubArray(std::vector<int> nums = {1,2,3,4,5}, int subs = 2){
    int minsum = *std::max_element(nums.begin(),nums.end());
    int maxsum = 0;
    //get the maxsum
    for(const int & n :nums){
        maxsum+=n;
    }
    int midsum;

    auto calcPartitions = [&](int sum){
        int partition =1;//init one array
        int currSum = 0;
        for(const int & n :nums){
            if(currSum + n <= sum){
                currSum += n;
            }else{
                partition++;
                currSum = n;
            }
        }
        return partition;

    };
    while(minsum<=maxsum){
        midsum = (minsum+maxsum)/2;
        // std::cout<<midsum<<"\n";

        if(calcPartitions(midsum) > subs){
            minsum = midsum +1;
        }else{
            maxsum = midsum-1;
        }
    }
    return minsum;
}

float gasStationsDistance(std::vector<int> stations = {} ,int newStations = 1){

}

int main(){
    auto res = gasStationsDistance();
    std::cout<<"final: "<<res<<std::endl;
    return 0;
}
