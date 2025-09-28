class Editor {
public:
	Editor ();
	Editor (Editor  &&) = default;
	Editor (const Editor  &) = default;
	Editor  &operator=(Editor  &&) = default;
	Editor  &operator=(const Editor  &) = default;
	~Editor ();

private:
	
};
