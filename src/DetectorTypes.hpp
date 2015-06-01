#ifndef _SONARIMAGEFEATURE_TYPES_HPP_
#define _SONARIMAGEFEATURE_TYPES_HPP_

#include <base/Eigen.hpp>
#include <base/samples/RigidBodyState.hpp>
#include <base/Time.hpp>
#include <base/samples/Pointcloud.hpp>
#include <vector>
#include <math.h>
#include "libsvm/svm.h"

namespace sonar_image_feature_extractor
{
  struct Destricptor{
    base::Vector3d dummy; //TODO
    
  };
  
   struct Feature{
     double confidence;
     base::Vector3d position;
     base::Vector3d size;
     Destricptor desc;
     
   };
   
   struct SonarConfig{
     base::Orientation orientation;
     
     double verticalOpening;
     double horizontalOpening;
     double maximumRange;
     double minimumRange;
   }; 
   
   
   struct SonarFeatures{
     base::Time time;
     SonarConfig conf;
     
     int number_of_features;
     int number_of_points;
     std::vector<Feature> features;
   };
   
  struct SonarPeak{
    
    base::Vector2d pos;
    double range;
    double angle;
    
    double norm(){
      return range;      
    }
    
    SonarPeak operator-(const SonarPeak& other){
      SonarPeak result;
      result.pos = this->pos - other.pos;
      result.range = result.pos.norm();
      result.angle = std::atan2(result.pos.y(),result.pos.x()); 
      
      return result;
    }
    
    
  };   
   
   
  /**
   * This class represents one 2d-cluster
   * The cluster is defined by the number of datapoints, and the range of values
   */   
    struct Cluster{
   
    Cluster() : number_of_points(0), minX(std::numeric_limits<double>::max()), minY(std::numeric_limits<double>::max()),
	maxX(-std::numeric_limits<double>::max()), maxY(-std::numeric_limits<double>::max()),
	min_range(std::numeric_limits<double>::max()), max_range(0.0), min_angle(M_PI), max_angle(M_PI)   {}
    
    int number_of_points;
    double minX, minY, maxX, maxY;
    double min_range, max_range, min_angle, max_angle;
    
    double variance;
    double contrast;
    double range_size;
    double angle_size;
    
  };   
   

   enum SMOOTH_MODE {
            GAUSSIAN = 0,
            AVG = 1,
            MEDIAN = 2
   };
   
   enum DEBUG_MODE {
	  NO_DEBUG = 0,
	  SMOOTHING = 1,
	  SOBEL = 2,
	  THRESHOLD = 3,
	  FEATURES = 4     
   };

    enum THRESHOLD_MODE {
	  ABSOLUTE = 0,
	  ADAPTIVE_MEAN = 1,
	  ADAPTIVE_GAUSSIAN = 2,
	  OTSU = 3
    };
    
    enum DISTANCE_MODE {
      EUKLIDIAN = 0,
      MAHALANOBIS =1
    };
  
  struct DetectorConfig{
    
    int blur;
    int morph;
    int sobel;
    double threshold;
    int adaptive_threshold_neighborhood;
    int cluster_min_size;
    int cluster_max_size;
    double cluster_noise;
    
    SMOOTH_MODE smooth_mode;
    DEBUG_MODE debug_mode;
    THRESHOLD_MODE threshold_mode;
    DISTANCE_MODE distance_mode;
    
    double sonar_max_range; //meter
    double sonar_opening_angle; //radian
    double ignore_min_range; //meter
   
  }; 
  
  struct SVMConfig{
    std::string svm_path;
    
    SVMType svm_type;
    KERNEL_TYPE kernel_type;
    int kernel_degree;
    double rbf_gamma;
    double coef0;
    
    //LEarning parameters    
    double cache_size;
    double stopping_eps;
    double C;
    std::vector<double> weights;
    std::vector<int> weight_labels;
    int use_shrinking;
    int use_probability;
    
    bool learn;
    
  };
  
  struct DebugData{
    std::vector<Cluster> cluster;
    double entropy;
    base::samples::Pointcloud points;
    
  };
  

} // end namespace sonar_image_feature_extractor

#endif // _DUMMYPROJECT_DUMMY_HPP_