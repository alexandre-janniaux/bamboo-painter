#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

template <typename T, typename Argv...>
std::unique_ptr<T>&& make_unique(Argv...) {
	
}

constexpr float pi = 3.14;

struct GraphicsNode {
	sf::Vector2f position;
	float angle;
	float distanceFromParent;
	std::vector<std::size_t> children;
	
	GraphicsNode(float angle, float distance, std::vector<std::size_t> children={}) :
		position({0.f,0.f}),
		angle(angle),
		distanceFromParent(distance),
		children(children) {}
		
};

class StickmanModel {
	public:
	static StickmanModel create(float neck_size, float arm_size, float body_size, float leg_size);
	void setRotation(std::size_t id, float rotation);
	
	const GraphicsNode& getRootNode() const;

	private:
	// TODO: be more SOLID
	friend class StickmanView;
	friend class StickmanController;
	void compute();
	void computeNode(GraphicsNode m_mainJoint, sf::Transform Identity);

	bool m_computed = false;
		
	GraphicsNode m_mainJoint;
	std::vector<std::unique_ptr<GraphicsNode>> m_joints;
};

class StickmanView : public sf::Drawable {
	public:
	void setModel(const StickmanModel& model);

	std::vector<float>&& getSquareDistanceFromPoint(const sf::Vector2f& point);

	protected:
	void render(sf::RenderTarget& target) override;
	
	private:
	std::shared_ptr<StickmanModel> m_model;
    void renderNode(sf::RenderTarget target, GraphicsNode node);

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
	
	private:
	StickmanModel* m_model=nullptr;
};




