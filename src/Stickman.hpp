#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <utility>
#include <type_traits>
#include <vector>


// Stephan T. Lavavej implementation
template <typename T, typename... Args>
std::unique_ptr<T> make_unique_helper(std::false_type, Args&&... args) {
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template <typename T, typename... Args>
std::unique_ptr<T> make_unique_helper(std::true_type, Args&&... args) {
	static_assert(std::extent<T>::value == 0,
				  "make_unique<T[N]>() is forbidden, please use make_unique<T[]>().");
	
	typedef typename std::remove_extent<T>::type U;
	return std::unique_ptr<T>(new U[sizeof...(Args)]{std::forward<Args>(args)...});
}

template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
	return make_unique_helper<T>(std::is_array<T>(), std::forward<Args>(args)...);
}
constexpr float pi = 3.14;

struct GraphicsNode {
	sf::Vector2f position;
	float angle;
	float distanceFromParent;
	std::vector<std::size_t> children;
	
	GraphicsNode(sf::Vector2f pos, float angle, float dist , std::vector<std::size_t> children) :
		position(pos),
		angle(angle),
		distanceFromParent(dist),
		children(children)
		{}
	
	GraphicsNode(float angle, float distance, std::vector<std::size_t> children) :
		position({0.f,0.f}),
		angle(angle),
		distanceFromParent(distance),
		children(children) {}
		
};

class StickmanModel {
	public:
	StickmanModel(float neck_size, float arm_size, float body_size, float leg_size);
	void setRotation(std::size_t id, float rotation);
	
	const GraphicsNode& getRootNode() const;

	private:
	// TODO: be more SOLID
	friend class StickmanView;
	friend class StickmanController;
	void compute();
	void computeNode(GraphicsNode& m_mainJoint, float angle);

	bool m_computed = false;
		
	GraphicsNode m_mainJoint;
	std::vector<std::unique_ptr<GraphicsNode>> m_joints;
};

class StickmanView : public sf::Drawable, public sf::Transformable {
	public:
	void setModel(StickmanModel& model);

	std::vector<float> getSquareDistanceFromPoint(const sf::Vector2f& point);

	protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
	private:
	StickmanModel* m_model;
    void renderNode(sf::RenderTarget& target, const GraphicsNode& node, float angle) const;

};

class StickmanEditorView : public StickmanView {
	public:
	/*
	*       Ajoute une marque autour du noeud sélectionné
	*/
	void highlightNode(std::size_t id, bool highlight);

	private:
	std::vector<bool> m_isHighlighted;
};

class StickmanController {
	public:
	void setModel(StickmanModel& model);

	/*
	*       Change la position du noeud, soit à la position donnée, soit au plus proche
	*       possible en satisfiant les contraintes de taille
	*/
	void setRigidGraphicsNodePosition(std::size_t node, const sf::Vector2f& position);
	
	void setNodeToDirection(std::size_t node, const sf::Vector2f& position);
	
	private:
	StickmanModel* m_model=nullptr;
};




