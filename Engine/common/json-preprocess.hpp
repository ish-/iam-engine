#pragma once
#include <string>

class JsonPreprocess {
	enum class CurrentState {
		Normal, Quote, QuoteIgnore, BeginComment, CommentLine, CommentBlock, CommentBlockEnd,
	};
public:
	static std::string removeComments (std::string _data) {
		std::string _ret = "";
		auto _state = CurrentState::Normal;
		for (char ch : _data) {
			if (_state == CurrentState::Normal) {
				if (ch == '"') {
					_ret += ch;
					_state = CurrentState::Quote;
				} else if (ch == '/') {
					_state = CurrentState::BeginComment;
				} else {
					_ret += ch;
				}
			} else if (_state == CurrentState::Quote) {
				if (ch == '"') {
					_ret += ch;
					_state = CurrentState::Normal;
				} else if (ch == '\\') {
					_ret += ch;
					_state = CurrentState::QuoteIgnore;
				} else {
					_ret += ch;
				}
			} else if (_state == CurrentState::QuoteIgnore) {
				_ret += ch;
				_state = CurrentState::Quote;
			} else if (_state == CurrentState::BeginComment) {
				_state = (ch == '/' ? CurrentState::CommentLine : CurrentState::CommentBlock);
			} else if (_state == CurrentState::CommentLine) {
				if (ch == '\r' || ch == '\n') {
					_ret += ch;
					_state = CurrentState::Normal;
				} else {
					_state = CurrentState::CommentLine;
				}
			} else if (_state == CurrentState::CommentBlock) {
				_state = (ch == '*' ? CurrentState::CommentBlockEnd : CurrentState::CommentBlock);
			} else if (_state == CurrentState::CommentBlockEnd) {
				_state = (ch == '*' ? CurrentState::CommentBlockEnd : (ch == '/' ? CurrentState::Normal : CurrentState::CommentBlock));
			}
		}
		return _ret;
	}
};