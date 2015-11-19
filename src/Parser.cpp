#include "Parser.h"
#include "gumbo.h"

Parser::Parser(std::string in) {
  Setinput_str(in);
  GumboOutput* output = gumbo_parse(in.c_str());
  std::string temp_out = cleantext(output->root);
  tokenize(temp_out);
  gumbo_destroy_output(&kGumboDefaultOptions, output);
}

std::string Parser::cleantext(GumboNode* node) {
  if (node->type == GUMBO_NODE_TEXT) {
    return std::string(node->v.text.text);
  } else if (node->type == GUMBO_NODE_ELEMENT &&
             node->v.element.tag != GUMBO_TAG_SCRIPT &&
             node->v.element.tag != GUMBO_TAG_STYLE) {
    std::string contents = "";
    GumboVector* children = &node->v.element.children;
    for (unsigned int i = 0; i < children->length; ++i) {
      const std::string text = cleantext((GumboNode*) children->data[i]);
      if (i != 0 && !text.empty()) {
        contents.append(" ");
      }
      contents.append(text);
    }
    return contents;
  } else {
    return "";
  }
}

void Parser::tokenize(std::string in) {
  std::string alphain;
  for (char& c : in) {
    if (c >= 32 && c < 255) {
      alphain.push_back(tolower(c));
    }
  }
  stemming::english_stem<> StemEnglish;
  boost::char_separator<char> sep(".,:-\n\t ");
  boost::tokenizer<boost::char_separator<char>> tokens(alphain, sep);
  for (const auto& t : tokens) {
    std::wstring word(t.begin(), t.end());
    StemEnglish(word);
    string op(word.begin(), word.end());
    parsed_out.push_back(op);
  }
}
