#pragma once

class Serial {
  public:
	Serial();
	~Serial();

	void Write(char);
	void Write(const char*);

  private:
	bool CanWrite();
};
