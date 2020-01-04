/**
 * @file Marker.h
 * @author Roberto Plaza Romero (Roberto.Plaza@alu.uclm.es)
 * @brief This file declares a class used to encapsulate the 
 * functions of a marker.
 * @version 1.0
 * @date 2020-01-04
 * 
 * @copyright Copyright (c) 2020 GPL v3.0
 * 
 */

#ifndef RVYA_MARKER__
#define RVYA_MARKER__


#include <AR/ar.h>

#include "Common.h"

#include <array>
#include <memory>


/**
 * @brief This class encapsulates the information of a Marker.
 * 
 * Easy handler for the functions of a Marker and some information 
 * regarding them. Also could be inherit in order to create a multipattern.
 * 
 */
class Marker
{
public:
    
    /**
     * @brief Construct a new Marker object
     * 
     * 
     * @param pattFilePath Path to the file of the Marker, commonly saved with 
     * a .patt extension.
     * @param pattWidth Width of the Marker in milimeters.
     * @param pattDispX Displacements of the Marker in X axis, used for the 
     * Multipattern.
     */
    Marker( const char *pattFilePath    = "Resources/Markers/Default.patt",
            double      pattWidth       = 120.0,
            double      pattDispX       = 0.0,
            double      pattDispY       = 0.0);

    virtual ~Marker ();

    /**
     * @brief Updates the information regarding the markers.
     * 
     * Each frame the Tick function should be called with the information
     * of the camera. The information regarding the net matrix will not be 
     * up-to-date untill the new Tick.
     * 
     * @param elapsedTime Time passed since the game started
     * @param data Pointer to the data of the camera
     */
    virtual void Tick(float elapsedTime);

    /**
     * @brief Gets information about itself based on the markers detected.
     * 
     * @param markers List of markets detected by ARToolKit.
     * @param count Number of markers detected, because fuck C.
     */
    void DetectYourself(ARMarkerInfo **markers, int count);

    /**
     * @brief Gets the Id of the marker.
     * 
     * @return Id of the marker. 
     */
    int GetId() const;

    /**
     * @brief Calculates the distance with other marker.
     * 
     * @param other The other marker.
     * @return double Distance in milimeters.
     */
    double Distance(const Marker &other) const;

    /**
     * @brief Calculates the distance from the camera.
     * 
     * @return double with the distance in milimeters.
     */
    double DistanceToCamera() const;

    /**
     * @brief Gets the X rotation of the object
     * 
     * @note Based on the code found in 
     * https://gamedev.stackexchange.com/questions/50963/how-to-extract-euler-angles-from-transformation-matrix
     * 
     * @return double with the rotation in degrees.
     */
    double GetYaw() const;

    /**
     * @brief Gets the Y rotation of the object
     * 
     * @note Based on the code found in 
     * https://gamedev.stackexchange.com/questions/50963/how-to-extract-euler-angles-from-transformation-matrix
     * 
     * @return double with the rotation in degrees.
     */
    double GetPitch() const;

    /**
     * @brief Gets the Z rotation of the object
     * 
     * @return double with the rotation in degrees.
     */
    double GetRoll() const;

    /**
     * @brief Returns if the marker is visible in the current frame.
     * 
     * @return true if the marker has been found.
     * @return false otherwise.
     */
    bool IsVisible() const;

    /**
     * @brief Get the Gl Trans Mat of the marker
     * 
     * @return Array with the OpenGL specific format.
     */
    const Transform &GetGlTransMat() const;

    /**
     * @brief Gets the location of the marker in the 3d world.
     * 
     * @return Vector with the x, y and z components of the position.
     */
    Vector GetLocation() const;

private:

    /**
     * @brief Entrypoint for every distance function.
     * 
     * @param trans target transform
     * @return double with the distance.
     */
    double DistanceTo(const Transform &trans) const;

private:

    /**
     * @brief Information about the transform of the Marker.
     * 
     */
    Transform       transform;

    /**
     * @brief Used for the multipatterns.
     * 
     */
    Center          displacement;

    /**
     * @brief Id of the marker.
     * 
     */
    int             id;

    /**
     * @brief Width in milimeters of the Marker.
     * 
     */
    double          size;

    /**
     * @brief bool to store if the marker is in sight
     * 
     */
    bool            isVisible;
    
};


/**
 * @note Several classes need to use a reference to a marker, 
 * in order to prevent possible problems, the intended way to 
 * instantiate a Marker is dynamically using smart pointers.
 * 
 */
typedef shared_ptr<Marker> ArMarker;


#endif // !RVYA_MARKER__