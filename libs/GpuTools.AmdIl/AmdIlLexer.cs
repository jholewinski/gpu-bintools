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
using System.Collections.Generic;
using System.IO;
using System.Text.RegularExpressions;

namespace GpuTools.AmdIl
{
  /// <summary>
  /// Lexical analyzer (tokenizer) for AMDIL.
  /// </summary>
  public class AmdIlLexer
  {

    #region Properties

    /// <summary>
    /// Indicates if more tokens are available in the stream.
    /// </summary>
    public bool HasTokens
    {
      get
      {
        return (currentIndex_< tokens_.Count);
      }
    }

    #endregion


    #region Constructors

    /// <summary>
    /// Constructor.
    /// </summary>
    /// <param name="stream">Stream containing the AMDIL content.</param>
    public AmdIlLexer(Stream stream)
    {
      tokens_ = new List<Token>();

      ParseStream(stream);
    }

    #endregion


    #region Public Methods

    /// <summary>
    /// Returns the next token in the stream.
    /// </summary>
    /// <returns>The next <see cref="Token"/>.</returns>
    public Token GetNextToken()
    {
      if(currentIndex_ >= tokens_.Count)
      {
        throw new InvalidOperationException("There are no more tokens left in the stream.");
      }

      return tokens_[currentIndex_++];
    }

    #endregion


    #region Private Methods

    /// <summary>
    /// Parses the input stream.
    /// </summary>
    /// <param name="stream">The input stream.</param>
    private void ParseStream(Stream stream)
    {
      using(StreamReader reader = new StreamReader(stream))
      {
        char  ch;

        AdvanceToNextNonWhiteSpace(reader);

        while(!reader.EndOfStream)
        {
          AdvanceToNextNonWhiteSpace(reader);
          ch = (char)reader.Read();

          if(char.IsNumber(ch) || ch == '-')
          {
            // We are starting a numeric constant.

            string constant = "";

            constant += ch;

            ch = (char)reader.Peek();
            while(char.IsNumber(ch) || ch == '.' || ch == 'x')
            {
              constant += ch;
              reader.Read();
              ch = (char)reader.Peek();
            }

            if(constant == "-")
            {
              throw new InvalidDataException("Minus must be followed by a constant.");
            }

            Token token = new Token(TokenType.Constant, constant, null);
            tokens_.Add(token);
          }
          else if(char.IsLetter(ch))
          {
            // We are starting an identifier.

            string    root = "";
            string    mask = null;
            TokenType type = TokenType.Identifier;

            root += ch;

            ch = (char)reader.Peek();
            while(char.IsLetterOrDigit(ch) || ch == '_')
            {
              root += ch;
              reader.Read();
              ch = (char)reader.Peek();
            }

            // Determine what type of identifier we have
            if(Regex.Match(root, "r[0-9]+").Success)
            {
              type = TokenType.Register;
            }
            else if(Regex.Match(root, "cb[0-9]+").Success)
            {
              type = TokenType.ConstantBuffer;
            }
            else if(Regex.Match(root, "l[0-9]+").Success)
            {
              type = TokenType.Literal;
            }
            else
            {
              type = TokenType.Identifier;
            }

            // Constant buffers require an index
            if(type == TokenType.ConstantBuffer)
            {
              string offset = "";

              if((char)reader.Read() != '[')
              {
                throw new InvalidDataException("Missing index on constant buffer.");
              }


              ch = (char)reader.Read();
              if(!char.IsNumber(ch))
              {
                throw new InvalidDataException("Constant buffer index must be an integer.");
              }

              while(char.IsNumber((char)reader.Peek()))
              {
                ch = (char)reader.Read();
                offset += ch;
              }


              if((char)reader.Read() != ']')
              {
                throw new InvalidDataException("Missing closing brace on constant buffer index.");
              }
            }

            // We have now parsed the root identifier.  However, we may still have a mask.
            if(ch == '.')
            {
              // We have a mask.
              mask = "";

              ch = (char)reader.Read();
              mask += ch;
              ch = (char)reader.Peek();

              while(char.IsLetterOrDigit(ch) || ch == '_')
              {
                mask += ch;
                reader.Read();
                ch = (char)reader.Peek();
              }
            }

            Token token = new Token(type, root, mask);
            tokens_.Add(token);
          }
          else
          {
            switch(ch)
            {
              case '(':
              {
                Token token = new Token(TokenType.OpenParenthesis);
                tokens_.Add(token);
                break;
              }
              case ')':
              {
                Token token = new Token(TokenType.CloseParenthesis);
                tokens_.Add(token);
                break;
              }
              case '[':
              {
                Token token = new Token(TokenType.OpenBrace);
                tokens_.Add(token);
                break;
              }
              case ']':
              {
                Token token = new Token(TokenType.CloseBrace);
                tokens_.Add(token);
                break;
              }
              case ',':
              {
                Token token = new Token(TokenType.Comma);
                tokens_.Add(token);
                break;
              }
              case ';':
              {
                // This is the start of a comment, so ignore until the end of the line
                AdvanceToNextLine(reader);
                break;
              }
              default:
              {
                throw new InvalidDataException(string.Format("Invalid character in input stream: {0:x}", (int)ch));
              }
            }
          }
        }
      }
    }

    /// <summary>
    /// Advances the given stream reader to the next non-whitespace character.
    /// </summary>
    /// <param name="reader">The stream reader.</param>
    private void AdvanceToNextNonWhiteSpace(StreamReader reader)
    {
      char ch;

      if(!char.IsWhiteSpace((char)reader.Peek()))
      {
        return;
      }

      do
      {
        if(reader.EndOfStream)
        {
          break;
        }

        reader.Read();
        ch = (char)reader.Peek();
      } while(char.IsWhiteSpace(ch));
    }

    /// <summary>
    /// Advances the given stream reader to the next line.
    /// </summary>
    /// <param name="reader">The stream reader.</param>
    private void AdvanceToNextLine(StreamReader reader)
    {
      char ch;

      do
      {
        if(reader.EndOfStream)
        {
          break;
        }

        ch = (char)reader.Read();
      } while(ch != '\n');
    }

    #endregion


    #region Fields

    private IList<Token> tokens_;
    private int          currentIndex_;

    #endregion

  }
}

