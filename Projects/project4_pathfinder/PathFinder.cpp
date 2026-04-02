#include "PathFinder.hpp"
#include <stdexcept>
#include <cstdlib>
#include <iostream>

PathFinder::PathFinder(const Image<Pixel> &img)
{
    load(img);
}

PathFinder::~PathFinder()
{
    clear();
}

void PathFinder::load(const Image<Pixel> &img)
{
    // TODO
}

void PathFinder::clear()
{
    // TODO
}

void PathFinder::checkImage(const Image<Pixel> &img) const
{
    // TODO
}

Coord PathFinder::getStart() const
{
    // TODO
    return Coord(); // placeholder
}

Coord PathFinder::getEnd() const
{
    // TODO
    return Coord(); // placeholder
}

void PathFinder::findPath(const std::string &strategy)
{
    // TODO, strategy is default at "NSWE". Must use Queue ADT to implement BFS algorithm
}

// BONUS: Same BFS as findPath(), plus GIF visualization
void PathFinder::findPathWithVisualization(const std::string &outfile, int frame_duration, int frame_gap, const std::string &strategy)
{
    // --- GIF setup (do not modify) ---
    int cell_size = 1; // each maze cell maps to a 1x1 pixel; increase for a larger GIF
    int gif_height = image.height() * cell_size;
    int gif_width = image.width() * cell_size;

    int frame_counter = 0; // tracks BFS steps; write a frame every frame_gap steps

    GifWriter gif;
    if (!GifBegin(&gif, (outfile + ".gif").c_str(), gif_width, gif_height, frame_duration, 8, true))
    {
        throw std::runtime_error("Failed to create GIF file.");
    }

    // ========================== BONUS TODO ==========================
    // This function is identical to findPath(), with three additions for visualization.
    // Copy your BFS logic from findPath() and add the following:
    //
    // --- Addition 1: Record each explored cell as a frame ---
    //   After you mark a coordinate as visited (e.g., color it BLUE), increment frame_counter.
    //   When frame_counter reaches frame_gap, write a frame and reset the counter:
    //
    //       frame_counter++;
    //       if (frame_counter >= frame_gap) {
    //           addFrameToGif(gif, frame_duration);
    //           frame_counter = 0;
    //       }
    //
    // --- Addition 2: Save the final image to a PNG ---
    //   After marking the solution path (GREEN exit, YELLOW path), write:
    //
    //       writeToFile(image, outfile + "_final_visual.png");
    //
    // --- Addition 3: Close the GIF before every exit point ---
    //   Before every return or throw in this function, you MUST call:
    //
    //       GifEnd(&gif);
    //
    //   This includes the normal success path AND the no-path-found error path.
    // ===========================================================

    GifEnd(&gif);
}

// Converts the current state of `image` into an RGBA pixel buffer and appends it as one GIF frame.
void PathFinder::addFrameToGif(GifWriter &gif, int frame_duration)
{
    int cell_size = 1; // each maze cell maps to a 1x1 pixel; increase for a larger GIF
    int gif_height = image.height() * cell_size;
    int gif_width = image.width() * cell_size;

    // Allocate RGBA buffer (4 bytes per pixel)
    std::vector<uint8_t> rgb_data(gif_height * gif_width * 4);

    // Map each maze cell's Pixel constant to an RGB color
    for (int r = 0; r < image.height(); ++r)
    {
        for (int c = 0; c < image.width(); ++c)
        {
            Pixel color;
            if (image(r, c) == WHITE)
            {
                color = {255, 255, 255};
            }
            else if (image(r, c) == BLACK)
            {
                color = {0, 0, 0};
            }
            else if (image(r, c) == RED)
            {
                color = {255, 0, 0};
            }
            else if (image(r, c) == GREEN)
            {
                color = {0, 255, 0};
            }
            else if (image(r, c) == BLUE)
            {
                color = {0, 0, 255};
            }
            else if (image(r, c) == YELLOW)
            {
                color = {255, 255, 0};
            }
            else
            {
                color = {0, 0, 0}; // default: treat unknown pixels as black
            }

            // Write this cell's color into the RGBA buffer (scaled by cell_size)
            for (int i = 0; i < cell_size; ++i)
            {
                for (int j = 0; j < cell_size; ++j)
                {
                    int pixel_row = r * cell_size + i;
                    int pixel_col = c * cell_size + j;
                    int index = (pixel_row * gif_width + pixel_col) * 4;
                    rgb_data[index + 0] = color.red;
                    rgb_data[index + 1] = color.green;
                    rgb_data[index + 2] = color.blue;
                    rgb_data[index + 3] = 255; // fully opaque
                }
            }
        }
    }

    // Append the completed frame to the GIF
    GifWriteFrame(&gif, rgb_data.data(), gif_width, gif_height, frame_duration, 8, true);
}

// Writes the current image (with any path markings) to a PNG file.
void PathFinder::writeSolutionToFile(const std::string &filename)
{
    writeToFile(image, filename);
}

// Returns true if both images have GREEN pixels at exactly the same coordinates.
// Ignores differences between non-GREEN pixels (e.g., BLUE vs WHITE visited markings).
bool compareImagesExit(const std::string &img1_str, const std::string &img2_str)
{
    Image<Pixel> img1 = readFromFile(img1_str);
    Image<Pixel> img2 = readFromFile(img2_str);
    if (img1.width() != img2.width() || img1.height() != img2.height())
    {
        return false;
    }
    for (int r = 0; r < img1.height(); ++r)
    {
        for (int c = 0; c < img1.width(); ++c)
        {
            if (img1(r, c) != img2(r, c) && (img1(r, c) == GREEN || img2(r, c) == GREEN))
            {
                return false;
            }
        }
    }
    return true;
}

// Returns true if every pixel in both images is identical (exact match).
bool compareImages(const std::string &img1_str, const std::string &img2_str)
{
    Image<Pixel> img1 = readFromFile(img1_str);
    Image<Pixel> img2 = readFromFile(img2_str);
    if (img1.width() != img2.width() || img1.height() != img2.height())
    {
        return false;
    }
    for (int r = 0; r < img1.height(); ++r)
    {
        for (int c = 0; c < img1.width(); ++c)
        {
            if (img1(r, c) != img2(r, c))
            {
                return false;
            }
        }
    }
    return true;
}