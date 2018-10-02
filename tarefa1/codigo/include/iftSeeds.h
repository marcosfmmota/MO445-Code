#ifndef IFT_SEEDS_H_
#define IFT_SEEDS_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "iftAdjacency.h"
#include "iftBMap.h"
#include "iftCommon.h"
#include "iftDataSet.h"
#include "iftFIFO.h"
#include "iftGQueue.h"
#include "iftImage.h"
#include "iftLabeledSet.h"
#include "iftLIFO.h"
#include "iftList.h"
#include "iftMathMorph.h"
#include "iftMImage.h"
#include "iftRegion.h"
#include "iftSet.h"

//! swig(newobject)
iftSet 	      *iftExtractRemovalMarkers(iftLabeledSet **s);
iftLabeledSet *iftLabelObjBorderSet(iftImage *bin, iftAdjRel *A);
iftLabeledSet *iftImageBorderLabeledSet(iftImage *img);
iftLabeledSet *iftLabelCompSet(iftImage *bin, iftAdjRel *A);
iftLabeledSet *iftFuzzyModelToLabeledSet(iftImage *model);
iftLabeledSet *iftMAdjustSeedCoordinates(iftLabeledSet *S, iftMImage *input, iftMImage *output);
iftLabeledSet *iftAdjustSeedCoordinates(iftLabeledSet *Sin, iftImage *orig, iftMImage *output);

iftSet        *iftImageBorderSet(iftImage *img);
iftLabeledSet *iftMultiObjectBorderLabeledSet(iftImage *img, iftAdjRel *A);


/**
 * @brief Gets the voxel's index from all object voxels (val > 0), returning them into a set
 * @param  label_img Label Image.
 * @return           Set with the voxel's indices from all objects.
 */
iftSet *iftObjectToSet(const iftImage *label_img);

/**
 * @brief Gets the voxel's index from all object voxels (val > 0), returning them into a list
 * @param  label_img Label Image.
 * @return           Set with the voxel's indices from all objects.
 *
 * @author Samuka Martins
 * @date Nov 16, 2017
 */
iftList *iftObjectsToList(const iftImage *label_img);


/**
 * @brief Finds and returns an iftSet with the coordinates of all border spels of a label image for a given adjacency <A>.
 * @param label Image label.
 * @param A Adjacency Relation.
 * @return The iftSet with the coordinates of all border spels of the label image <label>.
 */
iftSet *iftObjectBorderSet(const iftImage *label_img, iftAdjRel *Ain);
  iftSet *iftBackgroundBorderSet(const iftImage *label_img, iftAdjRel *Ain);


/**
 * @brief Finds and returns an iftBMap with the coordinates of all border spels of a label image for a given adjacency <A>.
 * @param label Image label.
 * @param A Adjacency Relation.
 * @param n_border_spels Number of border pixels/voxels of the label image that will be returned by reference.
 * @return The iftBMap with the coordinates of all border spels of the label image <label>.
 */
iftBMap *iftObjectBorderBitMap(const iftImage *label, const iftAdjRel *A, int *n_border_spels);


/**
 * @brief Stores all pixels from a Mask (Bin Image, except the background 0) to an input Set.
 * @author Samuel Martins
 * @dataset Jul 12, 2016
 * 
 * @param  mask Input Mask (Binary Image).
 * @return     The resulting Set.
 *
 * @note The input Set S may already have elements.
 */

void iftMaskImageToSet(const iftImage *mask, iftSet **S);

/**
 * @brief Sets the value <obj> in all voxels in the input image (which must have been allocated previously) from the input set.
 * @author Samuka Martins
 * @date Nov 16, 2017
 */
void iftSetToImage(const iftSet *S, iftImage *img, int obj);


/**
 * @brief Sets the value <obj> in all voxels in the input image (which must have been allocated previously) from the input List.
 * @author Samuka Martins
 * @date Apr 19, 2018
 */
void iftListToImage(const iftList *L, iftImage *img, int obj);


/**
 * @brief Create a list with the indices of all objects voxels from a mask (binary image).
 * @author Samuel Martins
 * @date Apr 24, 2018
 */
iftList *iftMaskToList(const iftImage *mask);


/**
 * @brief Insert an Labeled Set into image <img>. In order to save background seeds (which has 0-value)
 * to 1, use increment_label = true.
 * 
 * @author Samuka Martins
 * @date Dec 27, 2017
 */
//! swig()
void iftLabeledSetToImage(const iftLabeledSet *S, iftImage *img, bool increment_label);


/**
 * @brief Sets the value <obj> in all voxels in the input image (which must have been allocated previously) from the input integer array.
 * @author Samuel Martins
 * @date Apr 24, 2018
 */
void iftIntArrayToImage(const iftIntArray *iarr, iftImage *img, int obj);


/**
 * @brief Create an integer array with the indices of all objects voxels from a mask (binary image).
 * @author Samuel Martins
 * @date Apr 24, 2018
 */
iftIntArray *iftMaskToIntArray(const iftImage *mask);


/**
 * @brief   Copy all labeled region voxels to a Labeled Set. 
 * @author  Alexandre Falcao
 * @dataset Aug 1st, 2018
 * 
 * @param  label: Labeled region image, usually from 1 to n regions.
 * @param  S    : Labeled seed set.
 * @param  decrement_label : Boolean value to indicate when the labels must be decremented by 1. It is used when label 1 indicates background.  
 * @return The resulting labeled seed set.
 *
 * @note The labeled seed set S may already contain elements.
 */
  
  void iftRegionsToLabeledSet(const iftImage *label, iftLabeledSet **S, bool decrement_label);
  


iftSet        *iftEndPoints(iftImage *skel, iftAdjRel *A);
iftSet        *iftFindPathOnSkeleton(iftImage *skel, iftAdjRel *A, int src, int dst);
iftSet        *iftSkeletonPoints(iftImage *skel);


/**
 * @brief Return the Label Image's borders for a given Adjacency.
 * 
 * A border voxel is one with some adjacent voxel with different value or a frame voxel.
 * If keep_border_labels is true, it keeps the original label from the input label image.
 * Otherwise, all borders are binarized with value 1.
 * If include_image_frame is true, object pixels on image frame are included.
 * 
 * 
 * @param  label_img          (Multi) Label Image.
 * @param  Ain                Input adjacent used to find the borders. If NULL, a 4-neighborhood (2D) or 6-neighborhood (3D)
 *                            considered.
 * @param keep_border_labels  Keeps the original label from the input label image or binarize them with value 1.
 * @param include_image_frame Includes the object pixels on image frame.
 * @return                    An image with the found borders.
 *
 * @author Samuka Martins, Cesar Castelo
 * @date Nov 30, 2017
 */
iftImage *iftObjectBorders(const iftImage *label_img, const iftAdjRel *Ain, bool keep_border_labels,
                           bool include_image_frame);


/**
 * @brief Find the object borders of a labeled image and ALWAYS relabel them, even if the image
 * has multiple labels, since more than one object could have the same label.
 * It respects the label from the input Label Image to propagate the new label for the objects,
 * so that two adjacent objects with different labels in the input image will be also
 * different objects in the relabeled image.
 * 
 * @param  label_img Labeled Image (binary or multi-label)
 * @param  Ain       Input adjacent used to label the connected components within the borders,
 *                   If NULL, a 8-neighborhood (2D) or 26-neighborhood (3D) is considered.
 * @return           Image with the labeled object borders.
 * 
 * @author Samuka Martins, Cesar Castelo
 * @date Nov 30, 2017
 */
iftImage *iftFindAndLabelObjectBorders(const iftImage *label_img, const iftAdjRel *Ain);



iftImage      *iftEasyLabelComp(iftImage *bin, iftAdjRel *A);
iftImage      *iftLabelComp(iftImage *bin, iftAdjRel *A);


/**
 * @brief Select the Largest Component of a Binary Image.
 * 
 * @param bin Binary Image (0 = background, any value > 0 to represent the object).
 * @param Ain   Adjacency Relation. If NULL, it uses 4-neighborhood (2D) or 6-neighborhood (3D)
 * @return The largest component of the binary image with the object's label.
 */
iftImage *iftSelectLargestComp(const iftImage *bin, const iftAdjRel *Ain);


iftImage      *iftSelectSmallestComp(iftImage *bin, iftAdjRel *A);
iftImage      *iftSelectKLargestComp(iftImage *bin, iftAdjRel *A, int K);
iftImage      *iftSelectKSmallestComp(iftImage *bin, iftAdjRel *A, int K);
iftImage      *iftComponentArea(iftImage *bin, iftAdjRel *A);
iftImage      *iftSelectCompAboveArea(iftImage *bin, iftAdjRel *A, int thres);
iftImage      *iftSelectCompBelowArea(iftImage *bin, iftAdjRel *A, int thres);
iftImage      *iftSelectCompInAreaInterval(iftImage *bin, iftAdjRel *A, int thres_min, int thres_max);
iftImage      *iftRegionalMaxima(iftImage *img);
iftImage      *iftRegionalMinima(iftImage *img);
iftImage      *iftRegionalMaximaInRegion(iftImage *img, iftImage *mask);
iftImage      *iftRegionalMinimaInRegion(iftImage *img, iftImage *mask);
iftImage      *iftRootVoxels(iftImage *pred);
iftImage      *iftLeafVoxels(iftImage *pred, iftAdjRel *A);


  /* Assume that label contains regions with values in
     {1,2,..,n}. That is, label equal to zero is considered background
     and it does not define any region */

iftImage      *iftRegionArea(iftImage *label);


/**
 * @brief Select the Largest Component of a Labeled Image whose objects has label from 1 to n.
 * 
 * @param bin Binary Image
 * @param A   Adjacency Relation. If NULL, it uses 4-neighborhood (2D) or 6-neighborhood (3D)
 * @return The largest component of the binary image. Its label is the original region's label. 
 */
iftImage *iftSelectLargestRegion(const iftImage *label_img);

iftImage      *iftSelectSmallestRegion(iftImage *label);
iftImage      *iftSelectKLargestRegions(iftImage *label, int K);
iftImage      *iftSelectKLargestRegionsAndPropagateTheirLabels(iftImage *label, iftAdjRel *A, int K);
iftImage      *iftSelectKSmallestRegions(iftImage *label, int K);
iftImage      *iftSelectRegionsAboveArea(iftImage *label, int thres);
iftImage      *iftSelectRegionsAboveAreaAndPropagateTheirLabels(iftImage *label, int thres);
iftImage      *iftSelectRegionsBelowArea(iftImage *label, int thres);
/**
 * @brief Selects the regions with area size within the given interval.
 *
 * The regions are relabeled automatically in the output image.
 *
 * @param in_label The input label.
 * @param min_thres The minimum area size.
 * @param max_thres The maximum area size.
 * @return The relabeled image with removed regions.
 *
 */

iftImage      *iftSelectRegionsInAreaInterval(iftImage *label, int min_area, int max_area);
/**
 * @brief Selects the regions with area size within the given interval.
 *
 * The regions are relabeled automatically in-place, as opposed to iftSelectRegionsInAreaInterval.
 *
 * @param in_label The input label.
 * @param min_thres The minimum area size.
 * @param max_thres The maximum area size.
 * @sa iftSelectRegionsInAreaInterval
 *
 */
void           iftSelectRegionsInAreaIntervalInplace(iftImage *label, int min_area, int max_area);

  /* ---------------------------- */

iftImage      *iftLabelContPixel(iftImage *bin);
char           iftValidArcFromPixel(const iftImage *bin, const iftAdjRel *A, const iftAdjRel *L, const iftAdjRel *R, int p);

//! swig(newobject)
iftLabeledSet *iftReadSeeds(const char *filename, const iftImage *img);
void           iftWriteSeeds(const char *filename, iftLabeledSet* seed, const iftImage* image);

iftImage	  *iftSeedImageFromLabeledSet(iftLabeledSet* labeled_set, iftImage *image);

//! swig(newobject)
iftLabeledSet *iftLabeledSetFromSeedImage(iftImage* seed_image, bool decrement);
iftLabeledSet *iftLabeledSetFromSeedImageMarkersAndHandicap(iftImage* seed_image, iftImage *marker, iftImage *handicap);

/**
 * @brief This function computes the segmentation error components and relabels them to ensure that each one is given a
 * unique id (refactored from iftBorderMarkersForPixelSegmentation)
 *
 * @author Thiago Vallin Spina
 *
 * @param gt_image Ground truth image
 * @param label Segmentation result. It may be NULL, in which case we return an error component image with one component
 * per label
 * @param adj_relabeling Adjacency relation considered for relabeling the error components
 */
iftImage *iftRelabelSegmentationErrorComponents(iftImage *gt_image, iftImage *label, iftAdjRel *adj_relabeling);
iftLabeledSet *iftBorderMarkersForPixelSegmentation(iftImage *grad_image, iftImage *gt_image, float border_distance);
iftLabeledSet *iftGeodesicMarkersForSegmentation(iftImage *gt_image, iftImage *label);
iftLabeledSet* iftBorderMarkersForSuperpixelSegmentation(iftImage* label_image,iftImage* gt_image, iftDataSet* dataset);

//Pops the first "nelem" elements from "lset" with label "label"
iftLabeledSet* iftGetSeeds(iftLabeledSet* S, int nelem, int label);
iftLabeledSet* iftGetMisclassifiedSeeds(iftLabeledSet* S, int nelem, int label, iftImage* gt_image, iftImage* cl_image);

// Binary Segmentation only
int iftCheckNewSeeds(int *nelem, int length);

int iftSelectCircularRobotSeeds(iftImage *seed_image, iftBMap *used_seeds, iftImage *gt, double dist_border,
                                double max_marker_radius, double min_marker_radius, iftAdjRel *distance_border,
                                int center_seed);
//int iftMarkersFromMisclassifiedSeeds(iftImage* seed_image, iftLabeledSet* all_seeds, iftBMap* used_seeds, int nseeds,iftImage* gt_image, iftImage* cl_image, int dist_border, int max_marker_radius, int min_marker_radius);
int iftMarkersFromMisclassifiedSeeds(iftImage *seed_image, iftLabeledSet *all_seeds, iftBMap *used_seeds, int nseeds,
                                     int number_of_labels, iftImage *gt, iftImage *label, int dist_border,
                                     int max_marker_radius, int min_marker_radius);

void iftWriteSeedsOnImage(iftImage* image, iftLabeledSet* seed);

int iftRootVoxel(iftImage *pred, int p);

iftImage *iftFastLabelComp(const iftImage *bin, const iftAdjRel *Ain);

iftSet *iftBinaryMaskToSet(iftImage *mask);

iftImage *iftHBasins(iftImage *img, int H);
iftImage *iftHDomes(iftImage *img, int H);


/**
 * Apply a grid sampling on a binary mask image according to a radius, selecting randomly n_samples.
 *
 * If the number of required samples is greater than the total number of found samples in the grid, 
 * all samples are returned.
 * If n_samples is <= 0, it also returns all samples from the grid.
 * 
 * @warning This function only works with a binary mask with a single connect component.
 * @warning Your program should have the statement 'iftRandomSeed(time(NULL));' in order to guarantee
 * a true random selection.
 * 
 * @note There is a program to compute this function: ift/demo/Miscellaneous/Sampling/iftGridSamplingOnMask.c
 * @note See also: ift/demo/Miscellaneous/Sampling/iftExtractPatchesByGeodesicGridSamplingOnMask.c
 *  
 * @param  bin_mask  Binary mask where the topological grid sampling is applied.
 * @param  radius    Radius/stride between the samples of the grid.
 * @param  n_samples Number of required samples randomly extracted from the grid.
 *                   If it is greater than the total number of samples from the grid, all are returned.
 *                   If it <= 0, all samples is also returned.
 * @return           An array with the n_samples randomly chosen from the grid.
 * 
 * @author Samuka Martins
 * @date Apr 13, 2018
 */
iftIntArray *iftGridSamplingOnMask(const iftImage *bin_mask, float radius, long n_samples);

float iftEstimateGridOnMaskSamplingRadius
(iftImage *binMask, int nSamples);

/**
* @brief Performs a grid sampling on an multilabel image by assigning a proportional
* amount of seeds to each components area. The seeds are equally distributed within
* the object
* @author Felipe Belem
* @date June 28,2018
*
* @param label - Labeled image
* @param nSeeds - Number of desired seeds
*
* @return iftSet of seeds
*/
iftSet *iftMultiLabelGridSamplingOnMaskByArea
( iftImage *label, int nSeeds );

/**
 * @brief Apply a Grid Sampling for Patch Extraction where each grid point will be the central point
 * from its patch.
 * 
 * Each point of the grid is spaced each other by (stride_x, stride_y, stride_z).
 * The first grid point is the first one that fits the patch of size (patch_xsize, patch_ysize, patch_zsize).
 * It is guaranteed that the all patches centralized into the grid points will be entirely inside the image domain.
 * 
 * @param  img_dom  Domain of a given Image for grid sampling. Use the function iftGetImageDomain to get the domain of a given image.
 * @param  patch_xsize Patch's xsize.
 * @param  patch_ysize Patch's ysize.
 * @param  patch_zsize Patch's zsize.
 * @param  stride_x Stride (spacing) between the grid points on the x-axis.
 * @param  stride_y Stride (spacing) between the grid points on the y-axis.
 * @param  stride_z Stride (spacing) between the grid points on the z-axis.
 * @return          Integer array with the grid points.
 *
 * @author Samuel Martins
 * @date Jun 20, 2018.
 */
iftIntArray *iftGridSamplingForPatchExtraction(iftImageDomain img_dom, int patch_xsize, int patch_ysize,
                                               int patch_zsize, int stride_x, int stride_y, int stride_z);


/**
 * @brief Get a set of bounding boxes along an input image from an array of voxels.
 *
 * Each voxel, whose indices are in the integer array <voxel_indices>, corresponds to the central voxel
 * of a cubic bounding box of side <size>.
 * If a given bounding box is out of the image domain, its size and position are fit to it.
 * 
 * @param  img           Image used to get the voxel coordinate of the voxel indices.
 * @param  voxel_indices Indices of the central voxels on the image domain.
 * @param  size          Size of the cubic bounding boxes.
 * @return               Array with the found cubic bounding boxes along the image.
 *
 * @author Samuka Martins
 * @date Apr 25, 2018.
 */
iftBoundingBoxArray *iftBoundingBoxesAroundVoxels(const iftImage *img, const iftIntArray *voxel_indices, int size);

//! swig(newobject)
iftImage *iftLabelComponentsBySeeds(iftImage *comp, iftLabeledSet *seeds, bool incr);

#ifdef __cplusplus
} 
#endif

#endif
