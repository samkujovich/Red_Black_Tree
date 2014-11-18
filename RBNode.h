template<class Item>
class color_node {
protected:
	Item data_field;
	color_node* left_field;
	color_node* right_field;
	color_node* parent_field;
	enum Color { RED, BLACK };
	Color color_field;
public:
	color_node(const Item& init_data = Item(), color_node* init_left = NULL,
			color_node* init_right = NULL, Color init_color = RED, color_node* init_parent = NULL) {
		data_field = init_data;
		left_field = init_left;
		right_field = init_right;
		color_field = init_color;
		parent_field = init_parent;
	}
	// ACCESSOR & MUTATOR
	Item& data();
	color_node*& left();
	color_node*& right();
	Color color();
	color_node*& parent();
	void set_data(const Item& new_data);
	void set_left(color_node* new_left);
	void set_right(color_node* new_right);
	void set_color(Color new_color);
	void set_parent(color_node* new_parent);
	const Item& data() const;
	const color_node* left() const;
	const color_node* right() const;
	const Color color() const;
	const color_node* parent() const;
	bool is_leaf() const;
};

template<class Item>
Item& color_node<Item>::data() {
	return data_field;
}

template<class Item>
color_node<Item>*& color_node<Item>::left() {
	return left_field;
}

template<class Item>
color_node<Item>*& color_node<Item>::right() {
	return right_field;
}

template<class Item>
typename color_node<Item>::Color color_node<Item>::color() {
	return color_field;
}

template<class Item>
color_node<Item>*& color_node<Item>::parent() {
	return parent_field;
}

template<class Item>
void color_node<Item>::set_data(const Item& new_data) {
	data_field = new_data;
}

template<class Item>
void color_node<Item>::set_left(color_node* new_left) {
	left_field = new_left;
}

template<class Item>
void color_node<Item>::set_right(color_node* new_right) {
	right_field = new_right;
}

template<class Item>
void color_node<Item>::set_color(Color new_color) {
	color_field = new_color;
}

template<class Item>
void color_node<Item>::set_parent(color_node* new_parent) {
	parent_field = new_parent;
}

template<class Item>
const Item& color_node<Item>::data() const {
	return data_field;
}

template<class Item>
const color_node<Item>* color_node<Item>::left() const {
	return left_field;
}

template<class Item>
const color_node<Item>* color_node<Item>::right() const {
	return right_field;
}

template<class Item>
const typename color_node<Item>::Color color_node<Item>::color() const {
	return color_field;
}

template<class Item>
const color_node<Item>* color_node<Item>::parent() const {
	return parent_field;
}

template<class Item>
bool color_node<Item>::is_leaf() const {
	return (left_field == NULL) && (right_field == NULL);
}
