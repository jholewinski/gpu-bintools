// Author:
//       Justin Holewinski <justin.holewinski@gmail.com>
// 
// Copyright (c) 2011 Justin Holewinski
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

using System;
using System.IO;

namespace GpuTools.AmdIl
{
  /// <summary>
  /// Parser for AMDIL.
  /// </summary>
  public class AmdIlParser
  {
    #region Properties

    /// <summary>
    /// Gets/sets the verbose parsing flag.
    /// </summary>
    /// <remarks>
    /// If true, verbose parser output will be printed to the console to aid in parser debugging.
    /// </remarks>
    public bool Verbose { get; set; }

    #endregion

    /// <summary>
    /// Constructor.
    /// </summary>
    public AmdIlParser()
    {
      Verbose = false;
    }

    /// <summary>
    /// Parses an AMDIL file.
    /// </summary>
    /// <param name="filename">
    /// The file name.
    /// </param>
    /// <returns>The generated AstIlFile instance.</returns>
    public AmdIlFile ParseFile(string filename)
    {
      using(FileStream stream = new FileStream(filename, FileMode.Open))
      {
        return ParseStream(stream);
      }
    }

    /// <summary>
    /// Parses a stream containing an AMDIL file.
    /// </summary>
    /// <param name="stream">
    /// The stream to parse.
    /// </param>
    /// <returns>The generated AstIlFile instance.</returns>
    public AmdIlFile ParseStream(Stream stream)
    {
      AmdIlFile file   = new AmdIlFile();
      AmdIlLexer lexer = new AmdIlLexer(stream);

      lexer.GetNextToken();


      return file;
    }
  }
}

