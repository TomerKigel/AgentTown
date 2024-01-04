/*
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <https://unlicense.org>

Author:Tomer Kigel
Contact information:
	Gmail:	  Tomer.kigel@gmail.com
	Linkedin: https://www.linkedin.com/in/tomer-kigel/
	github:   https://github.com/TomerKigel
*/
#pragma once
#include <iostream>
#include <vector>

using std::string;

/// <summary>
/// Represents a connection interface for communication.
/// </summary>
class Connection
{
public:
    /// <summary>
    /// Get the unique identifier for the connection.
    /// </summary>
    /// <returns>The connection ID.</returns>
    virtual int get_id() const = 0;

    /// <summary>
    /// Run the connection logic.
    /// This method is responsible for handling the main execution flow of the connection.
    /// </summary>
    virtual void run() = 0;

    /// <summary>
    /// Read data from the connection.
    /// Implementations should define how data is read from the connection source.
    /// </summary>
    virtual void read() = 0;

    /// <summary>
    /// Send a message to the connection.
    /// </summary>
    /// <param name_="message">The message to be sent.</param>
    virtual void send(const std::string& message) = 0;

    /// <summary>
    /// Send a message to a specific list of connection IDs.
    /// </summary>
    /// <param name_="message">The message to be sent.</param>
    /// <param name_="id_list">The list of connection IDs to receive the message.</param>
    virtual void send_to_id_list(const std::string& message, const std::vector<int> id_list) = 0;

    /// <summary>
    /// Send a message to all connected clients.
    /// </summary>
    /// <param name_="message">The message to be sent.</param>
    virtual void send_all(const std::string& message) = 0;

    /// <summary>
    /// Disconnect the connection.
    /// Implementations should handle the necessary steps to disconnect and clean up resources.
    /// </summary>
    virtual void disconnect() = 0;
};